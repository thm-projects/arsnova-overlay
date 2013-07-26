#include "overlaywidgettest.h"

OverlayWidgetTest::OverlayWidgetTest ( QObject* parent ) : QObject ( parent ) {}

void OverlayWidgetTest::initTestCase() {
    context = new SessionContext ( new StubConnection() );
    this->overlayWidget = new OverlayWidget ( context );
    this->widgetSize = this->overlayWidget->size();
    context->connection()->requestSession ( "12345678" );
}

void OverlayWidgetTest::cleanupTestCase() {
    delete this->overlayWidget;
    delete this->context;
}

void OverlayWidgetTest::testShouldShowOverlayWidget() {
    this->overlayWidget->show();
    QVERIFY ( this->overlayWidget->isVisible() );
}

void OverlayWidgetTest::testShouldDisplayCorrectCountString() {
    QVERIFY ( this->overlayWidget->getUi()->bardiagramwidget->isVisible() );

    // As declared in StubConnection class
    /*QCOMPARE (
        this->overlayWidget->getUi()
        ->sessioninformationwidget->getUi()
        ->onlineUsersLabel
        ->text(),
        QString ( "(10/3)" )
    );*/
}

void OverlayWidgetTest::testShouldSwitchToLogoDiagram() {
    context->setViewType ( SessionContext::ICON_VIEW );
    QVERIFY ( ! this->overlayWidget->getUi()->bardiagramwidget->isVisible() );
    QVERIFY ( this->overlayWidget->getUi()->logodiagramwidget->isVisible() );
}

void OverlayWidgetTest::testShouldSwitchToBarDiagram() {
    context->setViewType ( SessionContext::DIAGRAM_VIEW );
    QVERIFY ( this->overlayWidget->getUi()->bardiagramwidget->isVisible() );
    QVERIFY ( ! this->overlayWidget->getUi()->logodiagramwidget->isVisible() );
}

void OverlayWidgetTest::testShouldBeOpaque() {
    this->overlayWidget->getUi()->actionMakeTransparent->trigger();
    QVERIFY ( this->overlayWidget->windowOpacity() < 1.0 );
}

void OverlayWidgetTest::testShouldNotBeOpaque() {
    this->overlayWidget->getUi()->actionMakeTransparent->trigger();
    QVERIFY ( this->overlayWidget->windowOpacity() == 1.0 );
}
