#ifndef INTERPOSEDQUESTION_H
#define INTERPOSEDQUESTION_H

#include <QtCore>

class InterposedQuestion {
    QString id;
    QString rev;
    QString sessionId;
    QString subject;
    QString text;
    QDateTime timestamp;
};

#endif // INTERPOSEDQUESTION_H
