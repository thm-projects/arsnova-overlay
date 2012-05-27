#include "overlaywidgettest.h"

OverlayWidgetTest::OverlayWidgetTest ( QObject* parent ) : QObject ( parent ) {}

void OverlayWidgetTest::initTestCase() {
    this->overlayWidget = new OverlayWidget();
}

void OverlayWidgetTest::cleanupTestCase() {
    delete this->overlayWidget;
}

void OverlayWidgetTest::testShouldShowOverlayWidget() {
    this->overlayWidget->show();
    QVERIFY ( this->overlayWidget->isVisible() );
}
