#ifndef SESSIONRESPONSE_H
#define SESSIONRESPONSE_H

#include <QtCore>

class SessionResponse {

public:
    explicit SessionResponse ( QString sessionId, QString shortName, QString name );
    ~SessionResponse();

    QString sessionId();
    QString shortName();
    QString name();

private:
    QString _sessionId;
    QString _shortName;
    QString _name;
};

#endif // SESSIONRESPONSE_H
