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
    virtual ~HttpConnection();
    void requestUnderstanding() override;
    void requestSession ( QString sessionKey ) override;
    void requestLoggedIn() override;
    void requestInterposedQuestions();
    void requestInterposedQuestion ( QString docID );

private:
    QNetworkAccessManager * networkAccessManager;
    QString sessionId;
    static QString hostname;

    QNetworkRequest createRequest ( QUrl url );
    bool isRedirect ( QNetworkReply * reply );

private slots:
    void handleReply ( QNetworkReply * reply );

};

#endif // HTTPCONNECTION_H
