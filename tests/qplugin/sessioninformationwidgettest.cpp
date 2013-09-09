#include "sessioninformationwidgettest.h"

SessionInformationWidgetTest::SessionInformationWidgetTest ( QObject* parent )
    : QObject ( parent ) {}

void SessionInformationWidgetTest::initTestCase() {
    this->sessionInformationWidget = new SessionInformationWidget();
}

void SessionInformationWidgetTest::cleanupTestCase() {
    delete this->sessionInformationWidget;
}
