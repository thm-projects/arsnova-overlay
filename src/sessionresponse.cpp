#include "sessionresponse.h"

SessionResponse::SessionResponse ( QString sessionId, QString shortName, QString name )
    : _sessionId ( sessionId ), _shortName ( shortName ), _name ( name ) {}

SessionResponse::~SessionResponse() {
}

QString SessionResponse::sessionId() {
    return this->_sessionId;
}

QString SessionResponse::shortName() {
    return this->_shortName;
}

QString SessionResponse::name() {
    return this->_name;
}
