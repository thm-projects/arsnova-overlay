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
    explicit HttpConnection ();
    void requestUnderstanding();
    void requestSession ( QString sessionKey );
    void requestLoggedIn();

private:
    QNetworkAccessManager * networkAccessManager;
    QString sessionId;

private slots:
    void handleReply ( QNetworkReply * reply );

signals:
    void requestError();
    void requestFinished ( SessionResponse response );
    void requestFinished ( UnderstandingResponse response );
    void requestFinished ( LoggedInResponse response );
};

#endif // HTTPCONNECTION_H
