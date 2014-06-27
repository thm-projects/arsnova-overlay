#include "httpconnection.h"

// 25 00 36 58

HttpConnection::HttpConnection ()
    : networkAccessManager ( new QNetworkAccessManager() ),
      cookies ( new QList<QNetworkCookie>() ) {
    connect ( networkAccessManager, SIGNAL ( finished ( QNetworkReply* ) ), this, SLOT ( handleReply ( QNetworkReply* ) ) );
    connect ( networkAccessManager, SIGNAL ( sslErrors ( QNetworkReply*,QList<QSslError> ) ) , this, SLOT ( onSslError ( QNetworkReply*,QList<QSslError> ) ) );

    this->networkAccessManager->get (
        this->createRequest (
            QUrl ( Settings::instance()->serverUrl().toString() + "/auth/login?type=guest" )
        )
    );

    this->websocket = new QWebSocket ( "https://arsnova.eu", QWebSocketProtocol::Version13 );

    connect ( this->websocket, &QWebSocket::textMessageReceived, [=] ( QString message ) {
        qDebug() << message;
        if ( message == "2::" ) {
            // Send Socket.IO Keepalive
            this->websocket->sendTextMessage ( "2::" );
        }

        if ( message.startsWith ( "5:::" ) ) {
            QJsonDocument doc = QJsonDocument::fromJson ( message.replace ( "5:::","" ).toUtf8() );
            if ( doc.isObject() && doc.object().contains ( "name" ) &&  doc.object().contains ( "args" ) ) {
                if ( doc.object().value ( "name" ) == "feedbackData" && doc.object().value ( "args" ).toArray().size() == 1 ) {
                    QJsonArray array = doc.object().value ( "args" ).toArray().at ( 0 ).toArray();
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
        }
    } );

    connect ( this->websocket, &QWebSocket::binaryMessageReceived, [=] ( QByteArray message ) {
        qDebug() << message;
    } );

    connect ( this->websocket, &QWebSocket::sslErrors, [=] ( QList<QSslError>  errors ) {
        // Ignore WebSocket SSL errors
        this->websocket->ignoreSslErrors ();
    } );

    connect ( this->websocket, &QWebSocket::stateChanged, [=] ( QAbstractSocket::SocketState state ) {
        qDebug() << state;
        if ( state == QAbstractSocket::ConnectedState ) {
            this->websocket->sendTextMessage ( "2::" );
        }
        if ( state == QAbstractSocket::UnconnectedState ) {
            // Try to reconnect
            //this->requestWebSocketId();
        }
    } );
}

HttpConnection::~HttpConnection() {
    delete networkAccessManager;
    delete cookies;
}

void HttpConnection::requestActiveUserCount() {
    this->networkAccessManager->get (
        this->createRequest (
            QUrl (
                Settings::instance()->serverUrl().toString() + "/session/" + sessionKey + "/activeusercount"
            )
        )
    );
}

void HttpConnection::requestSession ( QString sessionKey ) {
    this->sessionKey = sessionKey;
    this->networkAccessManager->get (
        this->createRequest (
            QUrl ( Settings::instance()->serverUrl().toString() + "/session/" + sessionKey )
        )
    );
}

void HttpConnection::requestFeedback() {
    this->networkAccessManager->get (
        this->createRequest (
            QUrl (
                Settings::instance()->serverUrl().toString() + "/session/" + sessionKey + "/feedback"
            )
        )
    );
}

void HttpConnection::requestAudienceQuestionsCount() {
    this->networkAccessManager->get (
        this->createRequest (
            QUrl (
                Settings::instance()->serverUrl().toString() + "/audiencequestion/?sessionkey=" + sessionKey
            )
        )
    );
}

void HttpConnection::requestWebSocketUrl() {
    this->networkAccessManager->get (
        this->createRequest (
            QUrl (
                Settings::instance()->serverUrl().toString() + "/socket/url/"
            )
        )
    );
}

void HttpConnection::requestWebSocketId () {
    if ( this->webSocketPath.startsWith ( "ws" ) ) {
        this->webSocketPath = this->webSocketPath.replace ( "ws", "http" );
    }
    this->networkAccessManager->get (
        this->createRequest (
            QUrl (
                this->webSocketPath + "/socket.io/1/"
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
    for ( QSslError error : errors.toStdList() ) {
        qDebug() << error.errorString();
    }
}

void HttpConnection::handleReply ( QNetworkReply * reply ) {
    reply->deleteLater();

    if ( reply->error() != QNetworkReply::NoError ) {
        qDebug() << reply->request().url() << reply->errorString();
        emit this->requestError();
    }

    if ( reply->url().path().contains ( "auth/login" ) ) {
        foreach ( QNetworkCookie cookie, qvariant_cast<QList<QNetworkCookie> > ( reply->header ( QNetworkRequest::SetCookieHeader ) ) ) {
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
    } else if ( reply->url().path().contains ( "/session" ) &&  !reply->url().path().contains ( "/online" ) ) {
        QString sessionKey = responseValue->property ( "keyword" ).toString();
        QString shortName = responseValue->property ( "shortName" ).toString();
        QString name = responseValue->property ( "name" ).toString();
        this->requestWebSocketUrl();
        emit this->requestFinished ( SessionResponse ( sessionKey, shortName, name ) );
    } else if ( reply->url().path().contains ( "/audiencequestion" ) ) {
        if ( ! responseValue->isArray() ) {
            return;
        }
        int read = 0;
        int unread = 0;

        for ( int i = 0; i < responseValue->toVariant().toList().size(); i++ ) {
            if ( ! responseValue->property ( i ).property ( "read" ).isBool() ) continue;

            if ( responseValue->property ( i ).property ( "read" ).toBool() ) {
                read++;
            } else {
                unread++;
            }
        }
        emit this->requestFinished ( AudienceQuestionCountResponse ( read, unread, read+unread ) );
    } else if ( reply->url().path().contains ( "/socket/url/" ) ) {
        qDebug() << QString::fromUtf8 ( response.data() );
        this->webSocketPath = QString::fromUtf8 ( response.data() );
        this->requestWebSocketId ();
    } else if ( reply->url().path().contains ( "/socket.io/1/" ) ) {
        if ( QString::fromUtf8 ( response.data() ).split ( ":" ).size() > 0 ) {
            QString webSocketId = QString::fromUtf8 ( response.data() ).split ( ":" ).at ( 0 );

            QNetworkRequest request = this->createRequest (
                                          QUrl (
                                              Settings::instance()->serverUrl().toString() + "/socket/assign"
                                          )
                                      );
            request.setHeader ( QNetworkRequest::ContentTypeHeader, "application/json" );
            QByteArray data = QByteArray ( "{\"session\":\"" + webSocketId.toUtf8() + "\"}" );
            qDebug() << data;
            this->networkAccessManager->post (
                request,
                data
            );

            QString wsPath = this->webSocketPath;
            QUrl wsUrl = QUrl ( wsPath.replace ( "http","ws" ) + "/socket.io/1/websocket/" + webSocketId );
            qDebug() << wsUrl;
            this->websocket->open ( wsUrl );
            qDebug() << "WS connect";
        } else {
            qDebug() << "WS close";
            this->websocket->close();
        }
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
    if ( this->username.isEmpty() || this->password.isEmpty() ) return request;
    QByteArray headerValue = "Basic "
                             + ( this->username + ":" + this->password ).toLocal8Bit().toBase64();
    request.setRawHeader ( "Authorization", headerValue );
    request.setRawHeader ( "Accept", "application/json" );
    request.setRawHeader ( "Content-Type", "application/json" );
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




