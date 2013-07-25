#ifndef AUDIENCEQUESTIONCOUNTESPONSE_H
#define AUDIENCEQUESTIONCOUNTESPONSE_H

#include <QtCore>
#include <stdarg.h>

class AudienceQuestionCountResponse {

public:
    explicit AudienceQuestionCountResponse ( int read, int unread, int total );
    int read();
    int unread();
    int total();

private:
    int _read;
    int _unread;
    int _total;
};

#endif // AUDIENCEQUESTIONCOUNTESPONSE_H
