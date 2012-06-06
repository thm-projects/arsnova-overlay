#include "logodiagramwidgettest.h"

LogoDiagramWidgetTest::LogoDiagramWidgetTest ( QObject * parent ) : QObject ( parent ) {}

void LogoDiagramWidgetTest::initTestCase() {
    this->logoDiagramWidget = new LogoDiagramWidget();
}

void LogoDiagramWidgetTest::cleanupTestCase() {
    delete this->logoDiagramWidget;
}

void LogoDiagramWidgetTest::testShouldShowLogoDiagramWidget() {
    this->logoDiagramWidget->show();
    QVERIFY ( this->logoDiagramWidget->isVisible() );
    QVERIFY ( this->logoDiagramWidget->getUi()->logoWidget->isVisible() );
}

void LogoDiagramWidgetTest::testShouldScaleSvgWidget() {
    QSize size = this->logoDiagramWidget->getUi()->logoWidget->size();
    QVERIFY ( size.height() == size.width() );
    QVERIFY ( this->logoDiagramWidget->size().height() == size.width() );
}
