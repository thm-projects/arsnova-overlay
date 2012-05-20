#include "sessionresponse.h"

SessionResponse::SessionResponse ( QString sessionId, QString shortName ) : _sessionId ( sessionId ), _shortName ( shortName ) {}

SessionResponse::~SessionResponse() {

}

QString SessionResponse::sessionId() {
    return this->_sessionId;
}

QString SessionResponse::shortName() {
    return this->_shortName;
}
