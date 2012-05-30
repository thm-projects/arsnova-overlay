#ifndef STUBCONNECTION_H
#define STUBCONNECTION_H

#include <../../home/pcvolkmer/Projekte/arsnovawidget/src/abstractconnection.h>


class StubConnection : public AbstractConnection {

public:
    virtual void requestLoggedIn();
    virtual void requestSession ( QString sessionKey );
    virtual void requestUnderstanding();
};

#endif // STUBCONNECTION_H
