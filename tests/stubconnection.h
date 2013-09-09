#ifndef STUBCONNECTION_H
#define STUBCONNECTION_H

#include "abstractconnection.h"

class StubConnection : public AbstractConnection {

public:
    virtual void requestActiveUserCount() override;
    virtual void requestSession ( QString sessionKey ) override;
    virtual void requestFeedback() override;
    virtual void requestAudienceQuestionsCount() override;
};

#endif // STUBCONNECTION_H
