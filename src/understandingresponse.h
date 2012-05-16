#ifndef UNDERSTANDINGRESPONSE_H
#define UNDERSTANDINGRESPONSE_H

#include <QtCore>
#include <stdarg.h>

class UnderstandingResponse {

public:
    explicit UnderstandingResponse ( int a, int b, int c, int d );
    ~UnderstandingResponse();

    QList< int > values();

private:
    QList<int> _values;
};

#endif // UNDERSTANDINGRESPONSE_H
