#include "qrcodewidget.h"

QRCodeWidget::QRCodeWidget ( SessionContext * context, QWidget* parent, Qt::WindowFlags f )
    : QWidget ( parent, f ), _ui ( new Ui::QRCodeWidget() ), _sessionContext ( context ) {
    _ui->setupUi ( this );
    this->setFullscreen ( false );

    connect ( _sessionContext, SIGNAL ( sessionChanged() ), this, SLOT ( onSessionChanged() ) );
}

QRCodeWidget::~QRCodeWidget() {
    delete _ui;
}

void QRCodeWidget::setFullscreen ( bool fullscreen ) {
    if ( fullscreen ) {
        // Rezize widget with 48px padding on each side
        this->resize (
            QApplication::desktop()->screenGeometry().width() - 96,
            QApplication::desktop()->screenGeometry().height() - 96
        );

        this->setWindowFlags (
            Qt::Window
            | Qt::FramelessWindowHint
            | Qt::WindowStaysOnTopHint
            | Qt::X11BypassWindowManagerHint
        );
    }

    this->adjustSize();

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
    _ui->urlLabel->setStyleSheet ( "font-size: " + this->neededFontSize() );
    this->setStyleSheet ( "background-color: white;" );
}

QSize QRCodeWidget::neededQRCodeSize() {
    int edgeSize = ( this->size().width() > this->size().height() )
                   ? this->size().height()
                   : this->size().width();

    return QSize ( edgeSize * .75, edgeSize * .75 );
}

QString QRCodeWidget::neededFontSize() {
    int edgeSize = this->neededQRCodeSize().height();
    // Aspect ratio QRCode - FontSize
    int fontSize = edgeSize / 14;
    return QString::number ( fontSize, 10 ) + "px";
}

const Ui::QRCodeWidget * const QRCodeWidget::getUi() {
    return this->_ui;
}

void QRCodeWidget::onSessionChanged() {
    this->setUrl ( QString ( "https://arsnova.thm.de/#id/" ) + _sessionContext->sessionId() );
}
