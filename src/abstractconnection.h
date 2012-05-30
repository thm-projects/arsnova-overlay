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
    virtual void requestUnderstanding() = 0;
    virtual void requestSession ( QString sessionKey ) = 0;
    virtual void requestLoggedIn() = 0;

signals:
    void requestError();
    void requestFinished ( SessionResponse response );
    void requestFinished ( UnderstandingResponse response );
    void requestFinished ( LoggedInResponse response );
};

#endif // ABSTRACTCONNECTION_H