#include "stubconnection.h"

void StubConnection::requestLoggedIn() {
    emit this->requestFinished ( LoggedInResponse ( 3 ) );
}

void StubConnection::requestSession ( QString sessionKey ) {
    if ( sessionKey.isEmpty() ) {
        emit this->requestError();
        return;
    }
    emit this->requestFinished ( SessionResponse ( "12345678", "STUB", "Stub Session" ) );
}

void StubConnection::requestUnderstanding() {
    emit this->requestFinished ( UnderstandingResponse ( 1, 2, 3, 4 ) );
}
