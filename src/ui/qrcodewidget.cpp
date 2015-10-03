#include "qrcodewidget.h"
#include "mainwindow.h"

QRCodeWidget::QRCodeWidget ( SessionContext * context, QStackedWidget * parent, Qt::WindowFlags f )
    : QWidget ( parent, f ), _ui ( new Ui::QRCodeWidget() ), _sessionContext ( context ) {
    _ui->setupUi ( this );

    this->parentBackup = parent;

    connect ( _sessionContext, SIGNAL ( sessionChanged() ), this, SLOT ( onSessionChanged() ) );
    connect ( _ui->toolButton, SIGNAL ( clicked ( bool ) ), this, SLOT ( onFullscreenButtonToggled ( bool ) ) );

    this->fullscreenWidget = nullptr;
    if ( parent != nullptr ) {
        this->fullscreenWidget = new QRCodeWidget ( this->_sessionContext, nullptr );
        this->fullscreenWidget->_ui->toolButton->hide();
        connect ( _sessionContext, SIGNAL ( sessionChanged() ), this->fullscreenWidget, SLOT ( onSessionChanged() ) );
        connect ( this->fullscreenWidget, SIGNAL ( closed() ), this,SLOT ( onFullscreenWidgetClosed() ) );
    }

    this->setUrl ( Settings::instance()->serverUrl().toString() );
}

QRCodeWidget::~QRCodeWidget() {
    disconnect ( _sessionContext, SIGNAL ( sessionChanged() ), this, SLOT ( onSessionChanged() ) );
    disconnect ( _ui->toolButton, SIGNAL ( clicked ( bool ) ), this, SLOT ( onFullscreenButtonToggled ( bool ) ) );
    delete _ui;
    if ( this->parentBackup != nullptr ) delete this->fullscreenWidget;
}

void QRCodeWidget::show() {
    this->adjustSize();
    QWidget::show();
}

bool QRCodeWidget::close() {
    emit this->closed();
    return QWidget::close();
}

QRCodeWidget* QRCodeWidget::getFullscreenWidget() const {
    return this->fullscreenWidget;
}

void QRCodeWidget::setFullscreen ( bool fullscreen, int screen ) {
    QRect screenGeometry = (
                               screen == -1 || screen > ( QApplication::desktop()->screenCount() - 1 )
                               ? QApplication::desktop()->availableGeometry ( QApplication::desktop()->screenCount() - 1 )
                               : QApplication::desktop()->availableGeometry ( screen )
                           );

    bool isOver = QApplication::desktop()->screenNumber ( this->parentBackup ) == screen || QApplication::desktop()->screenCount() == 1;

    if ( fullscreen && this->fullscreenWidget != nullptr ) {
        // Rezize widget with 48px padding on each side

        this->fullscreenWidget->resize (
            screenGeometry.width() - 96,
            screenGeometry.height() - 96
        );

        this->fullscreenWidget->setWindowFlags (
            Qt::Window
            | Qt::FramelessWindowHint
            | Qt::WindowStaysOnTopHint
            | Qt::X11BypassWindowManagerHint
        );
        this->fullscreenWidget->setVisible ( true );
        this->fullscreenWidget->adjustSize();

        QRect frect = this->fullscreenWidget->frameGeometry();
        frect.moveCenter ( screenGeometry.center() );
        //frect.moveCenter ( QApplication::desktop()->availableGeometry().center() );
        this->fullscreenWidget->move ( frect.topLeft() );
        if ( isOver ) {
            this->fullscreenWidget->_ui->toolButton->show();
        } else {
            this->fullscreenWidget->_ui->toolButton->hide();
        }
    } else if ( ! fullscreen && this->fullscreenWidget != nullptr ) {
        this->fullscreenWidget->close();
    } else if ( ! fullscreen ) {
        this->close();
    }

    this->_ui->toolButton->setChecked ( fullscreen );
    if ( this->fullscreenWidget != nullptr ) {
        this->fullscreenWidget->_ui->toolButton->setChecked ( fullscreen );
    }
}

void QRCodeWidget::setUrl ( QUrl url ) {
    QRCodeGenerator qrgen ( url.toString() );
    _ui->qrCodeLabel->setPixmap ( QPixmap::fromImage ( qrgen.generate().scaled ( this->neededQRCodeSize() ) ) );
    _ui->urlLabel->setText ( url.toString() );
}

void QRCodeWidget::adjustSize() {
    _ui->qrCodeLabel->resize ( this->neededQRCodeSize() );
    this->onSessionChanged();
    _ui->urlLabel->setStyleSheet ( "font-size: " + this->neededFontSize() );
    this->setStyleSheet ( "background-color: white;" );
}

QSize QRCodeWidget::neededQRCodeSize() {
    int edgeSize = this->size().height();

    return QSize ( edgeSize * .7, edgeSize * .7 );
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
    this->setUrl ( Settings::instance()->serverUrl().toString() + QString ( "/#id/" ) + _sessionContext->sessionId() );
}

void QRCodeWidget::onFullscreenButtonToggled ( bool enabled ) {
    this->setFullscreen ( enabled, Settings::instance()->screen() );
}

void QRCodeWidget::onFullscreenWidgetClosed() {
    this->_ui->toolButton->setChecked ( false );
}
