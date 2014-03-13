#include "qrcodewidgettest.h"
#include <settings.h>

QRCodeWidgetTest::QRCodeWidgetTest ( QObject * parent ) : QObject ( parent ) {}

void QRCodeWidgetTest::initTestCase() {
    this->connection = new StubConnection();
    this->context = new SessionContext ( this->connection );
    this->stackedWidget = new QStackedWidget();
    this->qrCodeWidget = new QRCodeWidget ( context, this->stackedWidget );
}

void QRCodeWidgetTest::cleanupTestCase() {
    delete this->qrCodeWidget;
    delete this->stackedWidget;
    delete this->context;
    delete this->connection;
}

void QRCodeWidgetTest::testShouldDisplayCorrectUrlOnStart() {
    QVERIFY ( this->qrCodeWidget->getUi()->urlLabel->text().startsWith(Settings::instance()->serverUrl().toString()) );
}

void QRCodeWidgetTest::testShouldDisplayCorrectUrlAfterSessionLogin() {
    this->context->connection()->requestSession ( "12345678" );
    QVERIFY ( this->qrCodeWidget->getUi()->urlLabel->text().endsWith("/#id/12345678") );
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
