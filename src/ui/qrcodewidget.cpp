#include "qrcodewidget.h"

QRCodeWidget::QRCodeWidget ( QWidget* parent, Qt::WindowFlags f )
    : QWidget ( parent, f ), _ui ( new Ui::QRCodeWidget() ) {
    _ui->setupUi ( this );
}

void QRCodeWidget::showUrl ( QUrl url ) {
    QRCodeGenerator qrgen ( url.toString() );
    QPixmap pixmap = QPixmap::fromImage ( qrgen.generate().scaled ( this->neededQRCodeSize() ) );
    _ui->qrCodeLabel->setPixmap ( pixmap );
    _ui->urlLabel->setText ( url.toString() );
    this->adjustSize();
    this->setWindowFlags (
        Qt::Window
        | Qt::FramelessWindowHint
        | Qt::WindowStaysOnTopHint
        | Qt::X11BypassWindowManagerHint
    );
    
    
    this->show();
}

void QRCodeWidget::adjustSize() {
    QSize qrCodeSize = this->neededQRCodeSize();
    _ui->urlLabel->setStyleSheet ( "font-size: 32px;" );
    this->setStyleSheet ( "background-color: white; padding: 48px;" );
}

QSize QRCodeWidget::neededQRCodeSize() {
    int edgeSize = ( QApplication::desktop()->screenGeometry().width() > QApplication::desktop()->screenGeometry().height() )
                   ? QApplication::desktop()->screenGeometry().height()
                   : QApplication::desktop()->screenGeometry().width();

    return QSize ( edgeSize/2, edgeSize/2 );
}
