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
        emit this->requestFinished ( RequestType::SESSION_REQUEST, responseValue );
    } else if ( this->httpClient->currentRequest().path().contains ( "by_session" ) ) {
        emit this->requestFinished ( RequestType::UNDERSTANDING_REQUEST, responseValue );
    } else if ( this->httpClient->currentRequest().path().contains ( "logged_in" ) ) {
        emit this->requestFinished ( RequestType::LOGGEDIN_REQUEST, responseValue );
    }
}
