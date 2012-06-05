#include "qrcodewidgettest.h"

QRCodeWidgetTest::QRCodeWidgetTest ( QObject* parent ) : QObject ( parent ) {}

void QRCodeWidgetTest::initTestCase() {
    this->qrCodeWidget = new QRCodeWidget();
}

void QRCodeWidgetTest::cleanupTestCase() {
    delete this->qrCodeWidget;
}

void QRCodeWidgetTest::testShouldDisplayQRCodeWidget() {
    this->qrCodeWidget->show();
    QVERIFY ( this->qrCodeWidget->isVisible() );
}

void QRCodeWidgetTest::testShouldDisplayCorrectUrl() {
    this->qrCodeWidget->setUrl ( QUrl ( "http://example.com" ) );
    QVERIFY ( this->qrCodeWidget->getUi()->urlLabel->text() == "http://example.com" );
}
