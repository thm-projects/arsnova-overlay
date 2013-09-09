#ifndef ABSTRACTCONNECTION_H
#define ABSTRACTCONNECTION_H

#include <QtNetwork>
#include <QtScript>

#include "sessionresponse.h"
#include "feedbackresponse.h"
#include "loggedinresponse.h"
#include "audiencequestioncountresponse.h"

class AbstractConnection : public QObject {
    Q_OBJECT

public:
    virtual void requestFeedback() = 0;
    virtual void requestSession ( QString sessionKey ) = 0;
    virtual void requestActiveUserCount() = 0;
    virtual void requestAudienceQuestionsCount() = 0;

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
    void requestFinished ( FeedbackResponse response );
    void requestFinished ( LoggedInResponse response );
    void requestFinished ( AudienceQuestionCountResponse response );
};

#endif // ABSTRACTCONNECTION_H
