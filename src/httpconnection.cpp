#include "httpconnection.h"

QString HttpConnection::hostname = "arsnova.thm.de";

HttpConnection::HttpConnection ()
    : networkAccessManager ( new QNetworkAccessManager() ),
      cookies ( new QList<QNetworkCookie>() ) {
    connect ( networkAccessManager, SIGNAL ( finished ( QNetworkReply* ) ), this, SLOT ( handleReply ( QNetworkReply* ) ) );

    this->networkAccessManager->get (
        this->createRequest (
            QUrl ( "https://" + HttpConnection::hostname + "/auth/login?type=guest" )
        )
    );
}

HttpConnection::~HttpConnection() {
    delete networkAccessManager;
    delete cookies;
}

void HttpConnection::requestActiveUserCount() {
    this->networkAccessManager->get (
        this->createRequest (
            QUrl (
                "https://" + HttpConnection::hostname + "/session/" + sessionKey + "/activeusercount"
            )
        )
    );
}

void HttpConnection::requestSession ( QString sessionKey ) {
    this->sessionKey = sessionKey;
    this->networkAccessManager->get (
        this->createRequest (
            QUrl ( "https://" + HttpConnection::hostname + "/session/" + sessionKey )
        )
    );
}

void HttpConnection::requestFeedback() {
    this->networkAccessManager->get (
        this->createRequest (
            QUrl (
                "https://" + HttpConnection::hostname + "/session/" + sessionKey + "/feedback"
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

void HttpConnection::handleReply ( QNetworkReply * reply ) {
    if (reply->error() != QNetworkReply::NoError) {
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
    }

    reply->deleteLater();
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
