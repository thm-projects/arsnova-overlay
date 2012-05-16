#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H

#include <QtNetwork>
#include <QtScript>

#include "sessionresponse.h"
#include "understandingresponse.h"
#include "loggedinresponse.h"

class HttpConnection : public QObject {
    Q_OBJECT

public:
    explicit HttpConnection ( QHttp * httpClient );
    void requestUnderstanding();
    void requestSession ( QString sessionKey );
    void requestLoggedIn();

    enum RequestType {
        SESSION_REQUEST,
        UNDERSTANDING_REQUEST,
        LOGGEDIN_REQUEST
    };

private:
    QHttp * httpClient;
    QString sessionId;

private slots:
    void handleResponse();

signals:
    void requestError();
    void requestFinished ( HttpConnection::RequestType type, QScriptValue * response );
    void requestFinished ( SessionResponse response );
    void requestFinished ( UnderstandingResponse response );
    void requestFinished ( LoggedInResponse response );
};

#endif // HTTPCONNECTION_H
