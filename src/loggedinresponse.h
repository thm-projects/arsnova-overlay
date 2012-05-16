#ifndef LOGGEDINRESPONSE_H
#define LOGGEDINRESPONSE_H

#include <QtCore>

class LoggedInResponse {

public:
    explicit LoggedInResponse ( int value );
    ~LoggedInResponse();

    int value();

private:
    int _value;

};

#endif // LOGGEDINRESPONSE_H
