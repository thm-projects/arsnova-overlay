#include "emotediagramwidgettest.h"

EmoteDiagramWidgetTest::EmoteDiagramWidgetTest ( QObject * parent ) : QObject ( parent ) {}

void EmoteDiagramWidgetTest::initTestCase() {
    this->emoteDiagramWidget = new EmoteDiagramWidget();
}

void EmoteDiagramWidgetTest::cleanupTestCase() {
    delete this->emoteDiagramWidget;
}

void EmoteDiagramWidgetTest::testShouldShowEmoteDiagramWidget() {
    this->emoteDiagramWidget->show();
    QVERIFY ( this->emoteDiagramWidget->isVisible() );
}

void EmoteDiagramWidgetTest::testShouldScaleSvgWidget() {
    QSize size = this->emoteDiagramWidget->getUi()->logoWidget->size();
    QVERIFY ( size.height() == size.width() );
    QVERIFY ( this->emoteDiagramWidget->size().height() == size.width() );
}
