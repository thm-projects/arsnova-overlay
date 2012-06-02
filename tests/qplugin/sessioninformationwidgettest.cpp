#include "sessioninformationwidgettest.h"

SessionInformationWidgetTest::SessionInformationWidgetTest ( QObject* parent )
    : QObject ( parent ) {}

void SessionInformationWidgetTest::initTestCase() {
    this->sessionInformationWidget = new SessionInformationWidget();
}

void SessionInformationWidgetTest::cleanupTestCase() {
    delete this->sessionInformationWidget;
}

void SessionInformationWidgetTest::testShouldDisplayCorrectProgressBar() {
    this->sessionInformationWidget->updateProgressBar ( 10,20 );
    QVERIFY (
        this->sessionInformationWidget->getUi()->progressBar->maximum() == 20
    );
    QVERIFY (
        this->sessionInformationWidget->getUi()->progressBar->value() == 10
    );
}

void SessionInformationWidgetTest::testShouldDisplayCorrectSessionName() {
    this->sessionInformationWidget->updateSessionLabel ( "Test","12345678" );
    QVERIFY (
        this->sessionInformationWidget->getUi()->sessionNameLabel->text() == "Test\n(12345678)"
    );
}

void SessionInformationWidgetTest::testShouldDisplayCorrectUserAndFeedbackCount() {
    this->sessionInformationWidget->updateCounterLabel ( 3,10 );
    QVERIFY (
        this->sessionInformationWidget->getUi()->onlineUsersLabel->text() == "(3/10)"
    );
}
