#include "qrcodewidget.h"

QRCodeWidget::QRCodeWidget ( QWidget* parent, Qt::WindowFlags f )
    : QWidget ( parent, f ), _ui ( new Ui::QRCodeWidget() ) {
    _ui->setupUi ( this );

    this->resize (
        QApplication::desktop()->screenGeometry().width() / 2,
        QApplication::desktop()->screenGeometry().height() / 2
    );

    this->adjustSize();
    this->setWindowFlags (
        Qt::Window
        | Qt::FramelessWindowHint
        | Qt::WindowStaysOnTopHint
        | Qt::X11BypassWindowManagerHint
    );

    QRect frect = frameGeometry();
    frect.moveCenter ( QApplication::desktop()->availableGeometry().center() );
    move ( frect.topLeft() );
}

void QRCodeWidget::setUrl ( QUrl url ) {
    QRCodeGenerator qrgen ( url.toString() );
    QPixmap pixmap = QPixmap::fromImage ( qrgen.generate().scaled ( this->neededQRCodeSize() ) );
    _ui->qrCodeLabel->setPixmap ( pixmap );
    _ui->urlLabel->setText ( url.toString() );
}

void QRCodeWidget::adjustSize() {
    _ui->qrCodeLabel->resize ( this->neededQRCodeSize() );
    _ui->urlLabel->setStyleSheet ( "font-size: 32px;" );
    this->setStyleSheet ( "background-color: white;" );
}

QSize QRCodeWidget::neededQRCodeSize() {
    int edgeSize = ( this->size().width() > this->size().height() )
                   ? this->size().height()
                   : this->size().width();

    return QSize ( edgeSize * .75, edgeSize * .75 );
}







