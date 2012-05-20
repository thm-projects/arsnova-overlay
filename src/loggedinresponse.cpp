#include "loggedinresponse.h"

LoggedInResponse::LoggedInResponse ( int value ) : _value ( value ) {}

LoggedInResponse::~LoggedInResponse() {

}

int LoggedInResponse::value() {
    return _value;
}

