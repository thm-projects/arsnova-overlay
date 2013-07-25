#include "audiencequestioncountresponse.h"

AudienceQuestionCountResponse::AudienceQuestionCountResponse ( int read, int unread, int total )
    : _read ( read ),
      _unread ( unread ),
      _total ( total ) {}

int AudienceQuestionCountResponse::read() {
    return this->_read;
}

int AudienceQuestionCountResponse::unread() {
    return this->_unread;
}

int AudienceQuestionCountResponse::total() {
    return this->_total;
}
