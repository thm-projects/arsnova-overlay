#ifndef UNDERSTANDINGRESPONSE_H
#define UNDERSTANDINGRESPONSE_H

#include <QtCore>
#include <stdarg.h>

class UnderstandingResponse {

public:

    enum Values {
        FEEDBACK_FASTER = 0,
        FEEDBACK_OK = 1,
        FEEDBACK_SLOWER = 2,
        FEEDBACK_AWAY = 3
    };

    public:
    explicit UnderstandingResponse ( int a, int b, int c, int d );
    ~UnderstandingResponse();

    QList< int > values();
    int count();

private:
    QList<int> _values;
    int _count;
};

#endif // UNDERSTANDINGRESPONSE_H
