#include "stubconnection.h"

void StubConnection::requestActiveUserCount() {
    emit this->requestFinished ( LoggedInResponse ( 3 ) );
}

void StubConnection::requestSession ( QString sessionKey ) {
    if ( sessionKey.isEmpty() ) {
        emit this->requestError();
        return;
    }
    emit this->requestFinished ( SessionResponse ( "12345678", "STUB", "Stub Session" ) );
}

void StubConnection::requestFeedback() {
    emit this->requestFinished ( FeedbackResponse ( 1, 2, 3, 4 ) );
}

void StubConnection::requestAudienceQuestionsCount() {
    emit this->requestFinished ( AudienceQuestionCountResponse ( 1, 2, 3 ) );
}
