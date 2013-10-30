#include "bardiagramwidgettest.h"

BarDiagramWidgetTest::BarDiagramWidgetTest ( QObject* parent ) : QObject ( parent ) {}

void BarDiagramWidgetTest::initTestCase() {
    this->barDiagramWidget = new BarDiagramWidget();
}

void BarDiagramWidgetTest::cleanupTestCase() {
    delete this->barDiagramWidget;
}

void BarDiagramWidgetTest::testShouldShowBarDiagramWidget() {
    this->barDiagramWidget->show();

    QVERIFY ( this->barDiagramWidget->isVisible() );
}
