#include "qrcodewidgettest.h"

QRCodeWidgetTest::QRCodeWidgetTest ( QObject * parent ) : QObject ( parent ) {}

void QRCodeWidgetTest::initTestCase() {
    this->connection = new StubConnection();
    this->qrCodeWidget = new QRCodeWidget ( new SessionContext ( this->connection ) );
}

void QRCodeWidgetTest::cleanupTestCase() {
    delete this->connection;
    delete this->qrCodeWidget;
}

void QRCodeWidgetTest::testShouldDisplayQRCodeWidget() {
    this->qrCodeWidget->show();
    QVERIFY ( this->qrCodeWidget->isVisible() );
}

void QRCodeWidgetTest::testShouldDisplayCorrectUrl() {
    this->qrCodeWidget->setUrl ( QUrl ( "https://ars.thm.de/id/87654321" ) );
    QVERIFY ( this->qrCodeWidget->getUi()->urlLabel->text() == "https://ars.thm.de/id/87654321" );
}

void QRCodeWidgetTest::testShouldDisplayCorrectUrlAfterSessionLogin() {
    this->connection->requestSession ( "12345678" );
    QVERIFY ( this->qrCodeWidget->getUi()->urlLabel->text() == "https://ars.thm.de/id/12345678" );
}
