#ifndef STUBCONNECTION_H
#define STUBCONNECTION_H

#include "abstractconnection.h"

class StubConnection : public AbstractConnection {

public:
    virtual void requestLoggedIn();
    virtual void requestSession ( QString sessionKey );
    virtual void requestUnderstanding();
};

#endif // STUBCONNECTION_H
