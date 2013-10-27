#include "qrcodewidget.h"
#include "mainwindow.h"

QRCodeWidget::QRCodeWidget ( SessionContext * context, QStackedWidget * parent, Qt::WindowFlags f )
    : QWidget ( parent, f ), _ui ( new Ui::QRCodeWidget() ), _sessionContext ( context ) {
    _ui->setupUi ( this );

    this->parentBackup = parent;

    connect ( _sessionContext, SIGNAL ( sessionChanged() ), this, SLOT ( onSessionChanged() ) );
    connect ( _ui->toolButton, SIGNAL ( clicked ( bool ) ), this, SLOT ( onFullscreenButtonToggled ( bool ) ) );
    connect ( _ui->transformComboBox, SIGNAL ( currentIndexChanged ( int ) ), this, SLOT ( onTransformationChanged() ) );

    this->fullscreenWidget = nullptr;
    if ( parent != nullptr ) {
        this->fullscreenWidget = new QRCodeWidget ( this->_sessionContext, nullptr );
        this->fullscreenWidget->_ui->toolButton->hide();
        this->fullscreenWidget->_ui->transformComboBox->hide();
        connect ( _sessionContext, SIGNAL ( sessionChanged() ), this->fullscreenWidget, SLOT ( onSessionChanged() ) );
        connect ( _ui->transformComboBox, SIGNAL ( currentIndexChanged ( int ) ), this->fullscreenWidget, SLOT ( onTransformationChanged() ) );
    }

    this->setUrl(Settings::instance()->serverUrl().toString());
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

void QRCodeWidget::setFullscreen ( bool fullscreen, int screen ) {
    QRect screenGeometry = (
                               screen == -1 || screen > ( QApplication::desktop()->screenCount() - 1 )
                               ? QApplication::desktop()->availableGeometry ( QApplication::desktop()->screenCount() - 1 )
                               : QApplication::desktop()->availableGeometry ( screen )
                           );

    if ( QApplication::desktop()->screenCount() > 1 && fullscreen && this->fullscreenWidget != nullptr ) {
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
        this->fullscreenWidget->move ( frect.topLeft() );
    } else if ( QApplication::desktop()->screenCount() > 1 && ! fullscreen && this->fullscreenWidget != nullptr ) {
        this->fullscreenWidget->close();
    } else if ( QApplication::desktop()->screenCount() == 1 && fullscreen && this->fullscreenWidget != nullptr ) {
        if ( fullscreen ) {
            // Rezize widget with 48px padding on each side
            this->setParent ( nullptr );
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
            this->setVisible ( true );
            this->adjustSize();
        } else {
            this->setParent ( this->parentBackup );
            if ( parentBackup != nullptr ) {
                this->parentBackup->addWidget ( this );
                this->parentBackup->setCurrentWidget ( this );
            }
            this->setVisible ( true );
            this->adjustSize();
        }

        QRect frect = frameGeometry();
        frect.moveCenter ( QApplication::desktop()->availableGeometry().center() );
        move ( frect.topLeft() );
    } else if ( QApplication::desktop()->screenCount() == 1 && ! fullscreen && this->fullscreenWidget != nullptr ) {
        this->setParent ( this->parentBackup );
        if ( parentBackup != nullptr ) {
            this->parentBackup->addWidget ( this );
            this->parentBackup->setCurrentWidget ( this );
        }
        this->setVisible ( true );
        this->adjustSize();
    }

    this->_ui->toolButton->setDown ( fullscreen );
}

void QRCodeWidget::setUrl ( QUrl url ) {
    QRCodeGenerator qrgen ( url.toString() );
    QPixmap pixmap = QPixmap::fromImage ( qrgen.generate().scaled ( this->neededQRCodeSize() ) );
    _ui->qrCodeLabel->setPixmap ( this->transform ( pixmap, ( Transformation ) this->_ui->transformComboBox->currentIndex() ) );
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
    this->setUrl ( Settings::instance()->serverUrl().toString() + QString ( "#id/" ) + _sessionContext->sessionId() );
}

void QRCodeWidget::onTransformationChanged() {
    if ( this->fullscreenWidget != nullptr ) {
        this->fullscreenWidget->_ui->transformComboBox->setCurrentIndex ( this->_ui->transformComboBox->currentIndex() );
    }
    this->onSessionChanged();
}

void QRCodeWidget::onFullscreenButtonToggled ( bool enabled ) {
    this->setFullscreen ( enabled, Settings::instance()->screen() );
}

QPixmap QRCodeWidget::transform ( QPixmap pixmap, Transformation transformation ) {
    QTransform translationTransform;
    qreal yScaling = 1;
    if ( transformation == Transformation::LEFT || transformation == Transformation::RIGHT ) yScaling = .9;
    int xRotate = 0;
    int yRotate = 0;

    switch ( transformation ) {
    case Transformation::TOP:
        xRotate = -20;
        break;
    case Transformation::BOTTOM:
        xRotate = 20;
        break;
    case Transformation::LEFT:
        yRotate = -20;
        break;
    case Transformation::RIGHT:
        yRotate = 20;
        break;
    case Transformation::NONE:
    default:
        break;
    }

    translationTransform.scale ( 1, yScaling );
    translationTransform.translate ( pixmap.width() /2, pixmap.height() /2 );
    translationTransform.rotate ( xRotate, Qt::XAxis );
    translationTransform.rotate ( yRotate, Qt::YAxis );
    translationTransform.translate ( -pixmap.width() /2, -pixmap.height() /2 );
    return pixmap.transformed ( translationTransform, Qt::SmoothTransformation );
}



