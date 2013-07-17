#include "qrcodewidgettest.h"

QRCodeWidgetTest::QRCodeWidgetTest ( QObject * parent ) : QObject ( parent ) {}

void QRCodeWidgetTest::initTestCase() {
    this->connection = new StubConnection();
    this->stackedWidget = new QStackedWidget();
    this->qrCodeWidget = new QRCodeWidget ( new SessionContext ( this->connection ), this->stackedWidget );
}

void QRCodeWidgetTest::cleanupTestCase() {
    delete this->connection;
    delete this->qrCodeWidget;
    delete this->stackedWidget;
}

void QRCodeWidgetTest::testShouldDisplayCorrectUrl() {
    this->qrCodeWidget->setUrl ( QUrl ( "https://arsnova.thm.de/#id/87654321" ) );
    QVERIFY ( this->qrCodeWidget->getUi()->urlLabel->text() == "https://arsnova.thm.de/#id/87654321" );
}

void QRCodeWidgetTest::testShouldDisplayCorrectUrlAfterSessionLogin() {
    this->connection->requestSession ( "12345678" );
    QVERIFY ( this->qrCodeWidget->getUi()->urlLabel->text() == "https://arsnova.thm.de/#id/12345678" );
}

void QRCodeWidgetTest::testShouldSwitchToFullscreenMode() {
    QSize size = this->qrCodeWidget->size();

    QTest::mouseClick ( this->qrCodeWidget->getUi()->toolButton, Qt::LeftButton );

    QVERIFY ( this->qrCodeWidget->getUi()->toolButton->isChecked() );

    if ( QApplication::desktop()->screenCount() == 1 ) {
        QVERIFY ( this->qrCodeWidget->size().height() == QApplication::desktop()->size().height() - 96 );
        QVERIFY ( this->qrCodeWidget->size().width() == QApplication::desktop()->size().width() - 96 );
    }
}

void QRCodeWidgetTest::testShouldSelectAllTransformationModes() {
    QTest::mouseClick ( this->qrCodeWidget->getUi()->toolButton, Qt::LeftButton );

    for ( int i = 0; i < this->qrCodeWidget->getUi()->transformComboBox->count(); i++ ) {
        QTest::mouseClick ( this->qrCodeWidget->getUi()->transformComboBox, Qt::LeftButton );
        this->qrCodeWidget->getUi()->transformComboBox->setCurrentIndex ( i );
        QCOMPARE ( this->qrCodeWidget->getUi()->transformComboBox->currentIndex(), i );
    }
}
