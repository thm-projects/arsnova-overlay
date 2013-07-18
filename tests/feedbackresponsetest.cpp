#include "feedbackresponsetest.h"

FeedbackResponseTest::FeedbackResponseTest ( QObject* parent ) : QObject ( parent ) {}

void FeedbackResponseTest::initTestCase() {
}

void FeedbackResponseTest::cleanupTestCase() {
}

void FeedbackResponseTest::testShouldReturnCorrectFeedbackCount() {
    FeedbackResponse fr ( 1, 2, 3, 4 );
    QVERIFY ( fr.count() == 10 );
}

void FeedbackResponseTest::testShouldReturnCorrectAverageResponse() {
    FeedbackResponse fr1 ( 5, 0, 5, 0 );
    QVERIFY ( fr1.averageRounded() == 1 );

    FeedbackResponse fr2 ( 5, 0, 0, 0 );
    QVERIFY ( fr2.averageRounded() == 0 );

    FeedbackResponse fr3 ( 0, 0, 0, 5 );
    QVERIFY ( fr3.averageRounded() == 3 );

    FeedbackResponse fr4 ( 2, 3, 5, 11 );
    QVERIFY ( fr4.averageRounded() == 2 );
}
