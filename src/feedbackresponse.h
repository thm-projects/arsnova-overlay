#ifndef FEEDBACKRESPONSE_H
#define FEEDBACKRESPONSE_H

#include <QtCore>
#include <stdarg.h>

class FeedbackResponse {

public:

    enum Values {
        FEEDBACK_FASTER = 0,
        FEEDBACK_OK = 1,
        FEEDBACK_SLOWER = 2,
        FEEDBACK_AWAY = 3
    };

public:
    explicit FeedbackResponse ( int a, int b, int c, int d );
    ~FeedbackResponse();

    QList< int > values();
    int count();

private:
    QList<int> _values;
    int _count;
};

#endif // FEEDBACKRESPONSE_H
