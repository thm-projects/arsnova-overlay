#ifndef SESSIONRESPONSE_H
#define SESSIONRESPONSE_H

#include <QtCore>

class SessionResponse {

public:
    explicit SessionResponse ( QString sessionId, QString shortName );
    ~SessionResponse();

    QString sessionId();
    QString shortName();

private:
    QString _sessionId;
    QString _shortName;
};

#endif // SESSIONRESPONSE_H
