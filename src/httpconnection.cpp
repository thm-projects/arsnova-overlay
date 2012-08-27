#include "httpconnection.h"

HttpConnection::HttpConnection ()
    : networkAccessManager ( new QNetworkAccessManager() ) {
    connect ( networkAccessManager, SIGNAL ( finished ( QNetworkReply* ) ), this, SLOT ( handleReply ( QNetworkReply* ) ) );

}

void HttpConnection::requestLoggedIn() {
    // Like ArsNova: ARSnova.models.Feedback.getUserFeedback()
    int timeLimit = 3;
    QString dcTimestamp = QString::number ( QDateTime::currentMSecsSinceEpoch() );

    this->networkAccessManager->get (
        QNetworkRequest (
            QUrl (
                "https://ars.thm.de/couchdb/arsnova/_design/logged_in/_view/count?_dc=" + dcTimestamp
                + "&startkey=[\"" + this->sessionId + "\"," + QString::number ( QDateTime::currentMSecsSinceEpoch() - ( timeLimit * 1000 * 60 ),10 ) + "]"
                + "&endkey=[\"" + this->sessionId + "\",{}]"
            )
        )
    );
}

void HttpConnection::requestSession ( QString sessionKey ) {
    this->networkAccessManager->get (
        QNetworkRequest (
            QUrl ( "https://ars.thm.de/couchdb/arsnova/_design/session/_view/by_keyword?key=\"" + sessionKey + "\"" )
        )
    );
}

void HttpConnection::requestUnderstanding() {
    // Like ArsNova: ARSnova.models.Feedback.getSessionFeedback()
    QString dcTimestamp = QString::number ( QDateTime::currentMSecsSinceEpoch() );

    this->networkAccessManager->get (
        QNetworkRequest (
            QUrl (
                "https://ars.thm.de/couchdb/arsnova/_design/understanding/_view/by_session?group=true&_dc=" + dcTimestamp
                + "&startkey=[\"" + this->sessionId + "\"]"
                + "&endkey=[\"" + this->sessionId + "\",{}]"
            )
        )
    );
}

void HttpConnection::requestInterposedQuestions() {
    this->networkAccessManager->get (
        QNetworkRequest (
            QUrl (
                "https://ars.thm.de/couchdb/arsnova/_design/interposed_question/_view/by_session?key=\""
                + this->sessionId + "\""
            )
        )
    );
}

void HttpConnection::requestInterposedQuestion ( QString docID ) {
    this->networkAccessManager->get (
        QNetworkRequest (
            QUrl (
                "https://ars.thm.de/couchdb/arsnova/" + docID
            )
        )
    );
}

void HttpConnection::handleReply ( QNetworkReply * reply ) {
    QByteArray response = reply->readAll();

    QScriptEngine scriptEngine;
    QScriptValue * responseValue = new QScriptValue ( scriptEngine.evaluate ( QString ( "(" ) + response.data() + ")" ) );

    if ( ! responseValue->isValid() ) {
        emit this->requestError();
        return;
    }

    if ( reply->url().path().contains ( "by_keyword" ) ) {
        this->sessionId = responseValue->property ( "rows" ).property ( 0 ).property ( "id" ).toString();
        if ( this->sessionId.isEmpty() ) {
            emit this->requestError();
            return;
        }
        QString sessionKey = responseValue->property ( "rows" ).property ( 0 ).property ( "key" ).toString();
        QString shortName = responseValue->property ( "rows" ).property ( 0 ).property ( "value" ).property ( "shortName" ).toString();
        QString name = responseValue->property ( "rows" ).property ( 0 ).property ( "value" ).property ( "name" ).toString();

        emit this->requestFinished ( SessionResponse ( sessionKey, shortName, name ) );
    } else if (
        reply->url().path().contains ( "by_session" )
        && reply->url().path().contains ( "understanding" )
    ) {
        int values[4] = {0,0,0,0};

        for ( int i = 0; i <= 3; i++ ) {
            QString key = responseValue->property ( "rows" ).property ( i ).property ( "key" ).property ( 1 ).toString();
            if ( key == "Bitte schneller" ) values[0] = responseValue->property ( "rows" ).property ( i ).property ( "value" ).toInteger();
            if ( key == "Kann folgen" ) values[1] = responseValue->property ( "rows" ).property ( i ).property ( "value" ).toInteger();
            if ( key == "Zu schnell" ) values[2] = responseValue->property ( "rows" ).property ( i ).property ( "value" ).toInteger();
            if ( key == "Nicht mehr dabei" ) values[3] = responseValue->property ( "rows" ).property ( i ).property ( "value" ).toInteger();
        }

        emit this->requestFinished ( UnderstandingResponse ( values[0], values[1], values[2], values[3] ) );
    } else if ( reply->url().path().contains ( "logged_in" ) ) {
        int value = responseValue->property ( "rows" ).property ( 0 ).property ( "value" ).toInteger();
        emit this->requestFinished ( LoggedInResponse ( value ) );
    } else if (
        reply->url().path().contains ( "by_session" )
        && reply->url().path().contains ( "interposed_question" )
    ) {
        QVariant interposedQuestions = responseValue->property ( "rows" ).toVariant();
        // TODO Transform into array of objects
    } else {
        // Single Document - check 'type' property
        QVariant responseDocument = responseValue->toVariant();
        if ( responseValue->property ( "type" ).equals ( "interposed_question" ) ) {
            // Interposed Question
        }
    }
    reply->deleteLater();
}
