#include "loggedinresponse.h"

LoggedInResponse::LoggedInResponse ( int value ) : _value ( value ) {}

LoggedInResponse::~LoggedInResponse() {
    qDebug() << "LoggedInResponse destroy";
}

int LoggedInResponse::value() {
    return _value;
}

