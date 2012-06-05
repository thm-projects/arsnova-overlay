#include "overlaywidgettest.h"

OverlayWidgetTest::OverlayWidgetTest ( QObject* parent ) : QObject ( parent ) {}

void OverlayWidgetTest::enterSessionId ( QLineEdit * lineEdit ) {
    QTest::keyClick ( lineEdit,  Qt::Key_0 );
    QTest::keyClick ( lineEdit,  Qt::Key_1 );
    QTest::keyClick ( lineEdit,  Qt::Key_2 );
    QTest::keyClick ( lineEdit,  Qt::Key_3 );
    QTest::keyClick ( lineEdit,  Qt::Key_4 );
    QTest::keyClick ( lineEdit,  Qt::Key_5 );
    QTest::keyClick ( lineEdit,  Qt::Key_6 );
    QTest::keyClick ( lineEdit,  Qt::Key_7 );
    QTest::keyClick ( lineEdit,  Qt::Key_Enter );
}


void OverlayWidgetTest::initTestCase() {
    this->overlayWidget = new OverlayWidget ( new StubConnection() );
    this->widgetSize = this->overlayWidget->size();
}

void OverlayWidgetTest::cleanupTestCase() {
    delete this->overlayWidget;
}

void OverlayWidgetTest::testShouldExitOnExitButtonClicked() {
    delete this->overlayWidget;
    this->overlayWidget = new OverlayWidget ( new StubConnection() );
    this->overlayWidget->show();

    QVERIFY ( this->overlayWidget->getUi()->loginwidget->isVisible() );
    QTest::mouseClick ( this->overlayWidget->getUi()->loginwidget->getUi()->exitButton, Qt::LeftButton );

    QVERIFY ( this->overlayWidget->isEnabled() );
    this->overlayWidget = new OverlayWidget ( new StubConnection() );
}

void OverlayWidgetTest::testShouldShowOverlayWidget() {
    this->overlayWidget->show();
    QVERIFY ( this->overlayWidget->isVisible() );
}

void OverlayWidgetTest::testShouldNotDisplayBarDiagramWithoutSessionLogin() {
    QVERIFY ( this->overlayWidget->getUi()->loginwidget->isVisible() );

    QTest::keyClick ( this->overlayWidget->getUi()->loginwidget->getUi()->sessionIdEdit,  Qt::Key_Enter );

    QVERIFY ( this->overlayWidget->getUi()->loginwidget->isVisible() );
}

void OverlayWidgetTest::testShouldDisplayBarDiagramAfterSessionLogin() {
    QVERIFY ( this->overlayWidget->getUi()->loginwidget->isVisible() );

    this->enterSessionId ( this->overlayWidget->getUi()->loginwidget->getUi()->sessionIdEdit );

    QVERIFY ( this->overlayWidget->getUi()->bardiagramwidget->isVisible() );
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

void OverlayWidgetTest::testShouldSwitchToLogin() {
    this->overlayWidget->getUi()->actionChangeSession->trigger();
    QVERIFY ( this->overlayWidget->getUi()->loginwidget->isVisible() );
}
