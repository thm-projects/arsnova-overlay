#ifndef ABSTRACTCONNECTION_H
#define ABSTRACTCONNECTION_H

#include <QtNetwork>
#include <QtScript>

#include "sessionresponse.h"
#include "understandingresponse.h"
#include "loggedinresponse.h"

class AbstractConnection : public QObject {
    Q_OBJECT

public:
    virtual void requestFeedback() = 0;
    virtual void requestSession ( QString sessionKey ) = 0;
    virtual void requestActiveUserCount() = 0;

    virtual void setCredentials ( QString username, QString password ) final {
        this->username = username;
        this->password = password;
    };

protected:
    QString username;
    QString password;

signals:
    void requestError();
    void requestFinished ( SessionResponse response );
    void requestFinished ( UnderstandingResponse response );
    void requestFinished ( LoggedInResponse response );
};

#endif // ABSTRACTCONNECTION_H
