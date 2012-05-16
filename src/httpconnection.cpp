#include "httpconnection.h"

HttpConnection::HttpConnection ( QHttp * httpClient ) : QObject(), httpClient ( httpClient ) {
    connect ( this->httpClient, SIGNAL ( requestFinished ( int,bool ) ), this, SLOT ( handleResponse() ) );
}

void HttpConnection::requestLoggedIn() {
    // Like ArsNova: ARSnova.models.Feedback.getUserFeedback()
    int timeLimit = 3;
    QString dcTimestamp = QString::number ( QDateTime::currentMSecsSinceEpoch() );

    this->httpClient->get (
        "/couchdb/arsnova/_design/logged_in/_view/count?_dc=" + dcTimestamp
        + "&startkey=[\"" + this->sessionId + "\"," + QString::number ( QDateTime::currentMSecsSinceEpoch() - ( timeLimit * 1000 * 60 ),10 ) + "]"
        + "&endkey=[\"" + this->sessionId + "\",{}]"
    );
}

void HttpConnection::requestSession ( QString sessionKey ) {
    this->httpClient->get ( "/couchdb/arsnova/_design/session/_view/by_keyword?key=\"" + sessionKey + "\"" );
}

void HttpConnection::requestUnderstanding() {
    // Like ArsNova: ARSnova.models.Feedback.getSessionFeedback()
    QString dcTimestamp = QString::number ( QDateTime::currentMSecsSinceEpoch() );

    this->httpClient->get (
        "/couchdb/arsnova/_design/understanding/_view/by_session?group=true&_dc=" + dcTimestamp
        + "&startkey=[\"" + this->sessionId + "\"]"
        + "&endkey=[\"" + this->sessionId + "\",{}]"
    );
}

void HttpConnection::handleResponse() {
    QByteArray response = this->httpClient->readAll();
    QScriptEngine scriptEngine;
    QScriptValue * responseValue = new QScriptValue ( scriptEngine.evaluate ( QString ( "(" ) + response.data() + ")" ) );

    if ( ! responseValue->isValid() ) {
        //emit this->requestError();
        //return;
    }

    if ( this->httpClient->currentRequest().path().contains ( "by_keyword" ) ) {
        this->sessionId = responseValue->property ( "rows" ).property ( 0 ).property ( "id" ).toString();
        QString sessionKey = responseValue->property ( "rows" ).property ( 0 ).property ( "key" ).toString();
        QString shortName = responseValue->property ( "rows" ).property ( 0 ).property ( "value" ).property ( "shortName" ).toString();
        emit this->requestFinished ( SessionResponse ( sessionKey, shortName ) );
    } else if ( this->httpClient->currentRequest().path().contains ( "by_session" ) ) {
        int values[4] = {0,0,0,0};

        for ( int i = 0; i <= 3; i++ ) {
            QString key = responseValue->property ( "rows" ).property ( i ).property ( "key" ).property ( 1 ).toString();
            if ( key == "Bitte schneller" ) values[0] = responseValue->property ( "rows" ).property ( i ).property ( "value" ).toInteger();
            if ( key == "Kann folgen" ) values[1] = responseValue->property ( "rows" ).property ( i ).property ( "value" ).toInteger();
            if ( key == "Zu schnell" ) values[2] = responseValue->property ( "rows" ).property ( i ).property ( "value" ).toInteger();
            if ( key == "Nicht mehr dabei" ) values[3] = responseValue->property ( "rows" ).property ( i ).property ( "value" ).toInteger();
        }

        emit this->requestFinished ( UnderstandingResponse ( values[0], values[1], values[2], values[3] ) );
    } else if ( this->httpClient->currentRequest().path().contains ( "logged_in" ) ) {
        int value = responseValue->property ( "rows" ).property ( 0 ).property ( "value" ).toInteger();
        emit this->requestFinished ( LoggedInResponse ( value ) );
    }
}
