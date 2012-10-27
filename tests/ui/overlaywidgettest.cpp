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
}

void OverlayWidgetTest::testShouldShowOverlayWidget() {
    this->overlayWidget->show();
    QVERIFY ( this->overlayWidget->isVisible() );
}

void OverlayWidgetTest::testShouldDisplayCorrectCountString() {
    QVERIFY ( this->overlayWidget->getUi()->bardiagramwidget->isVisible() );

    // As declared in StubConnection class
    QCOMPARE (
        this->overlayWidget->getUi()
        ->sessioninformationwidget->getUi()
        ->onlineUsersLabel
        ->text(),
        QString ( "(10/3)" )
    );
}

void OverlayWidgetTest::testShouldSwitchToLogoDiagram() {
    QVERIFY ( ! this->overlayWidget->getUi()->actionSwitchView->isChecked() );
    this->overlayWidget->getUi()->actionSwitchView->trigger();
    QVERIFY ( this->overlayWidget->getUi()->actionSwitchView->isChecked() );
    QVERIFY ( ! this->overlayWidget->getUi()->bardiagramwidget->isVisible() );
    QVERIFY ( this->overlayWidget->getUi()->logodiagramwidget->isVisible() );
}

void OverlayWidgetTest::testShouldSwitchToBarDiagram() {
    QVERIFY ( this->overlayWidget->getUi()->actionSwitchView->isChecked() );
    this->overlayWidget->getUi()->actionSwitchView->trigger();
    QVERIFY ( ! this->overlayWidget->getUi()->actionSwitchView->isChecked() );
    QVERIFY ( this->overlayWidget->getUi()->bardiagramwidget->isVisible() );
    QVERIFY ( ! this->overlayWidget->getUi()->logodiagramwidget->isVisible() );
}

void OverlayWidgetTest::testShouldShowQRCodeWidget() {
    this->overlayWidget->getUi()->actionShowQRCode->trigger();
    this->qrCodeWidget = ( QRCodeWidget * ) QApplication::widgetAt (
                             QApplication::desktop()->screenGeometry().width() / 2,
                             QApplication::desktop()->screenGeometry().height() / 2
                         )->parentWidget();

    if ( this->qrCodeWidget == nullptr ) QFAIL ( "Test failed: No Widget found" );

    const QMetaObject * metaObject = this->qrCodeWidget->metaObject();
    QVERIFY (
        metaObject->property ( metaObject->indexOfProperty ( "objectName" ) ).read ( this->qrCodeWidget ) == "QRCodeWidget"
    );
    QVERIFY (
        qrCodeWidget->isVisible()
    );
}

void OverlayWidgetTest::testShouldNotShowQRCodeWidget() {
    if ( this->qrCodeWidget == nullptr ) QFAIL ( "Test failed: No Widget found" );
    this->overlayWidget->getUi()->actionShowQRCode->trigger();
    QVERIFY (
        ! qrCodeWidget->isVisible()
    );
}

void OverlayWidgetTest::testShouldBeFullscreen() {
    this->overlayWidget->getUi()->actionFullscreen->trigger();
    int width = QApplication::desktop()->screenGeometry().width();
    int height = QApplication::desktop()->screenGeometry().height();

    QVERIFY ( this->overlayWidget->width() == width );
    QVERIFY ( this->overlayWidget->height() == height );
}

void OverlayWidgetTest::testShouldNotBeFullscreen() {
    this->overlayWidget->getUi()->actionFullscreen->trigger();
    QVERIFY ( this->overlayWidget->width() == this->widgetSize.width() );
    QVERIFY ( this->overlayWidget->height() == this->widgetSize.height() );
}

void OverlayWidgetTest::testShouldBeOpaque() {
    this->overlayWidget->getUi()->actionMakeTransparent->trigger();
    QVERIFY ( this->overlayWidget->windowOpacity() < 1.0 );
}

void OverlayWidgetTest::testShouldNotBeOpaque() {
    this->overlayWidget->getUi()->actionMakeTransparent->trigger();
    QVERIFY ( this->overlayWidget->windowOpacity() == 1.0 );
}
