#include "httpconnection.h"

HttpConnection::HttpConnection ()
    : networkAccessManager ( new QNetworkAccessManager() ),
      cookies ( new QList<QNetworkCookie>() ) {
    connect ( networkAccessManager, SIGNAL ( finished ( QNetworkReply* ) ), this, SLOT ( handleReply ( QNetworkReply* ) ) );
    connect ( networkAccessManager, SIGNAL ( sslErrors ( QNetworkReply*,QList<QSslError> ) ) , this, SLOT ( onSslError ( QNetworkReply*,QList<QSslError> ) ) );

    this->networkAccessManager->get (
        this->createRequest (
            QUrl ( Settings::instance()->serverUrl().toString() + "/api/auth/login?type=guest" )
        )
    );
    this->requestWebSocketUrl();

    this->websocket = new QWebSocket ( "", QWebSocketProtocol::Version13 );

    connect ( this->websocket, &QWebSocket::textMessageReceived, [=] ( QString message ) {

        // Connected to Socket.IO
        if ( message.startsWith ( "0" ) ) {
            message = message.remove ( 0,1 );
            QJsonDocument doc = QJsonDocument::fromJson ( message.toUtf8() );
            if ( doc.isObject() && doc.object().contains ( "pingInterval" ) ) {
                this->wsPingInterval = doc.object().value ( "pingInterval" ).toInt();
            }
            if ( doc.isObject() && doc.object().contains ( "sid" ) ) {
                this->webSocketId = doc.object().value ( "sid" ).toString();

                QNetworkRequest request = this->createRequest (
                                              QUrl (
                                                  Settings::instance()->serverUrl().toString() + "/api/socket/assign"
                                              )
                                          );
                request.setHeader ( QNetworkRequest::ContentTypeHeader, "application/json" );
                QByteArray data = QByteArray ( "{\"session\":\"" + this->webSocketId.toUtf8() + "\"}" );

                this->networkAccessManager->post (
                    request,
                    data
                );
            }
        }

        // Ping
        if ( message.startsWith ( "3" ) ) {
            QTimer::singleShot ( this->wsPingInterval, this, &HttpConnection::sendPong );
        }

        // Socket.IO Init
        if ( message.startsWith ( "40" ) ) {
            QTimer::singleShot ( this->wsPingInterval, this, &HttpConnection::sendPong );
        }

        // Regular message from ARSnova
        if ( message.startsWith ( "42" ) ) {
            message = message.remove ( 0,2 );
            QJsonDocument doc = QJsonDocument::fromJson ( message.toUtf8() );
            if ( doc.isArray() && doc.array().contains ( "feedbackData" ) ) {
                QJsonArray array = doc.array().last().toArray();
                emit this->requestFinished (
                    FeedbackResponse (
                        array.at ( FeedbackResponse::FEEDBACK_OK ).toInt(),
                        array.at ( FeedbackResponse::FEEDBACK_FASTER ).toInt(),
                        array.at ( FeedbackResponse::FEEDBACK_SLOWER ).toInt(),
                        array.at ( FeedbackResponse::FEEDBACK_AWAY ).toInt()
                    )
                );
            }
        }
    } );

    connect ( this->websocket, &QWebSocket::sslErrors, [=] ( QList<QSslError>  errors ) {
        // Ignore WebSocket SSL errors
        this->websocket->ignoreSslErrors ();
    } );

    connect ( this->websocket, &QWebSocket::stateChanged, [=] ( QAbstractSocket::SocketState state ) {
        if ( state == QAbstractSocket::UnconnectedState ) {
            // Try to reconnect
            this->requestSession ( this->sessionKey );
        }
    } );
}

void HttpConnection::sendPong() {
    this->websocket->sendTextMessage ( "2" );
}

HttpConnection::~HttpConnection() {
    delete networkAccessManager;
    delete cookies;
}

void HttpConnection::requestActiveUserCount() {
    this->networkAccessManager->get (
        this->createRequest (
            QUrl (
                Settings::instance()->serverUrl().toString() + "/api/session/" + sessionKey + "/activeusercount"
            )
        )
    );
}

void HttpConnection::requestSession ( QString sessionKey ) {
    this->sessionKey = sessionKey;
    this->networkAccessManager->get (
        this->createRequest (
            QUrl ( Settings::instance()->serverUrl().toString() + "/api/session/" + sessionKey )
        )
    );

    QString message = "42[\"setSession\",{\"keyword\":\"" + sessionKey + "\"}]";
    this->websocket->sendTextMessage ( message );
}

void HttpConnection::requestFeedback() {
    this->networkAccessManager->get (
        this->createRequest (
            QUrl (
                Settings::instance()->serverUrl().toString() + "/api/session/" + sessionKey + "/feedback"
            )
        )
    );
}

void HttpConnection::requestAudienceQuestionsCount() {
    this->networkAccessManager->get (
        this->createRequest (
            QUrl (
                Settings::instance()->serverUrl().toString() + "/api/audiencequestion/readcount?sessionkey=" + sessionKey
            )
        )
    );
}

void HttpConnection::requestWebSocketUrl() {
    this->networkAccessManager->get (
        this->createRequest (
            QUrl (
                Settings::instance()->serverUrl().toString() + "/api/socket/url/"
            )
        )
    );
}

bool HttpConnection::isRedirect ( QNetworkReply* reply ) {
    for ( QNetworkReply::RawHeaderPair header : reply->rawHeaderPairs().toStdList() ) {
        if ( header.first == "Location" ) {
            QString newLocation = header.second.replace ( "%2522","\"" );
            this->networkAccessManager->get (
                this->createRequest (
                    newLocation
                )
            );
            return true;
        }
    }

    return false;
}

void HttpConnection::onSslError ( QNetworkReply* reply, QList< QSslError > errors ) {
    reply->ignoreSslErrors ( errors );
}

void HttpConnection::handleReply ( QNetworkReply * reply ) {
    reply->deleteLater();

    if ( reply->error() != QNetworkReply::NoError ) {
        emit this->requestError();
    }

    if ( reply->url().path().contains ( "auth/login" ) ) {
        for ( QNetworkCookie cookie : ( qvariant_cast<QList<QNetworkCookie> > ( reply->header ( QNetworkRequest::SetCookieHeader ) ) ).toStdList() ) {
            this->addCookie ( cookie );
        }
        return;
    }

    if ( this->isRedirect ( reply ) ) return;

    QByteArray response = reply->readAll();

    QScriptEngine scriptEngine;
    QScriptValue * responseValue = new QScriptValue ( scriptEngine.evaluate ( QString ( "(" ) + QString::fromUtf8 ( response.data() ) + ")" ) );

    if ( ! responseValue->isValid() ) {
        emit this->requestError();
        return;
    }

    if (
        reply->url().path().contains ( "/feedback" )
    ) {
        QVariant variant = responseValue->property ( "values" ).toVariant();

        if ( variant.toList().size() != FeedbackResponse::FEEDBACK_AWAY + 1 ) return;

        emit this->requestFinished (
            FeedbackResponse (
                variant.toList().at ( FeedbackResponse::FEEDBACK_OK ).toInt(),
                variant.toList().at ( FeedbackResponse::FEEDBACK_FASTER ).toInt(),
                variant.toList().at ( FeedbackResponse::FEEDBACK_SLOWER ).toInt(),
                variant.toList().at ( FeedbackResponse::FEEDBACK_AWAY ).toInt()
            )
        );
    } else if ( reply->url().path().contains ( "/activeusercount" ) ) {
        int value = responseValue->toInteger();
        emit this->requestFinished ( LoggedInResponse ( value ) );
    } else if ( reply->url().path().contains ( "/session" ) ) {
        QString sessionKey = responseValue->property ( "keyword" ).toString();
        QString shortName = responseValue->property ( "shortName" ).toString();
        QString name = responseValue->property ( "name" ).toString();
        emit this->requestFinished ( SessionResponse ( sessionKey, shortName, name ) );
    } else if ( reply->url().path().contains ( "/audiencequestion/readcount" ) ) {
        int read = responseValue->property ( "read" ).toInteger();
        int unread = responseValue->property ( "unread" ).toInteger();

        emit this->requestFinished ( AudienceQuestionCountResponse ( read, unread, read+unread ) );
    } else if ( reply->url().path().contains ( "/api/socket/url/" ) ) {
        this->webSocketPath = QString::fromUtf8 ( response.data() );
        QUrl wsUrl = QUrl ( this->webSocketPath.replace ( "http","ws" ) + "/socket.io/?EIO=2&transport=websocket" );
        this->websocket->open ( wsUrl );
    }
}

QNetworkRequest HttpConnection::createRequest ( QUrl url ) {
    QNetworkRequest request;
    request.setUrl ( url );
    if ( this->cookies->size() > 0 ) {
        request.setRawHeader (
            "Cookie",
            this->cookies->at ( 0 ).name() + "=" + this->cookies->at ( 0 ).value()
        );
    }
    request.setRawHeader ( "Accept", "application/json" );
    request.setRawHeader ( "Content-Type", "application/json" );

    if ( this->username.isEmpty() || this->password.isEmpty() ) return request;
    QByteArray headerValue = "Basic "
                             + ( this->username + ":" + this->password ).toLocal8Bit().toBase64();
    request.setRawHeader ( "Authorization", headerValue );
    return request;
}

void HttpConnection::addCookie ( QNetworkCookie cookie ) {
    for ( int i = 0; i < this->cookies->size(); i++ ) {
        if (
            this->cookies->at ( i ).name() == cookie.name()
            && this->cookies->at ( i ).domain() == cookie.domain()
        ) {
            this->cookies->removeAt ( i );
        }
    }
    this->cookies->append ( cookie );
}
