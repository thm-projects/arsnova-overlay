#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H

#include <QtNetwork>
#include <QtScript>
#include <QtWebSockets/QWebSocket>

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
    void requestAudienceQuestionsCount() override;
    void requestWebSocketUrl();
    void requestWebSocketId ();

private:
    QNetworkAccessManager * networkAccessManager;
    QString sessionKey;
    QString webSocketPath;
    QList<QNetworkCookie> * cookies;
    QWebSocket * websocket;

    QNetworkRequest createRequest ( QUrl url );
    bool isRedirect ( QNetworkReply * reply );
    void addCookie ( QNetworkCookie cookie );

private slots:
    void handleReply ( QNetworkReply * reply );
    void onSslError ( QNetworkReply*,QList<QSslError> );

};

#endif // HTTPCONNECTION_H
