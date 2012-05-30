#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H

#include <QtNetwork>
#include <QtScript>

#include "abstractconnection.h"
#include "sessionresponse.h"
#include "understandingresponse.h"
#include "loggedinresponse.h"

class HttpConnection : public AbstractConnection {
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

};

#endif // HTTPCONNECTION_H
