#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H

#include <QtNetwork>
#include <QtScript>

#include "abstractconnection.h"
#include "sessionresponse.h"
#include "feedbackresponse.h"
#include "loggedinresponse.h"
#include "settings.h"

class HttpConnection : public AbstractConnection {
    Q_OBJECT

public:
    explicit HttpConnection ();
    virtual ~HttpConnection();
    void requestFeedback() override;
    void requestSession ( QString sessionKey ) override;
    void requestActiveUserCount() override;

private:
    QNetworkAccessManager * networkAccessManager;
    QString sessionKey;
    QList<QNetworkCookie> * cookies;

    QNetworkRequest createRequest ( QUrl url );
    bool isRedirect ( QNetworkReply * reply );
    void addCookie ( QNetworkCookie cookie );

private slots:
    void handleReply ( QNetworkReply * reply );

};

#endif // HTTPCONNECTION_H
