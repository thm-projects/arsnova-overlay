#ifndef STUBCONNECTION_H
#define STUBCONNECTION_H

#include "abstractconnection.h"

class StubConnection : public AbstractConnection {

public:
    virtual void requestLoggedIn() override;
    virtual void requestSession ( QString sessionKey ) override;
    virtual void requestUnderstanding() override;
};

#endif // STUBCONNECTION_H
