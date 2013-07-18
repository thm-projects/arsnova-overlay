#ifndef FEEDBACKRESPONSETEST_H
#define FEEDBACKRESPONSETEST_H

#include <QtTest>

#include "feedbackresponse.h"

class FeedbackResponseTest : public QObject {

    Q_OBJECT

public:
    explicit FeedbackResponseTest ( QObject * parent = nullptr );

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testShouldReturnCorrectFeedbackCount();
    void testShouldReturnCorrectAverageResponse();
};

#endif // FEEDBACKRESPONSETEST_H
