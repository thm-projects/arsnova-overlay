#include "overlaywidget.h"

#include "qrcodegenerator.h"

const int OverlayWidget::ySize = 80;
const int OverlayWidget::xSize = 180;
const int OverlayWidget::httpUpdateInterval = 10;

OverlayWidget::OverlayWidget ( AbstractConnection * connection, QWidget * parent, Qt::WindowFlags f )
    : QWidget ( parent, f ) , ui ( new Ui::OverlayWidget() ), connection ( connection ) {
    ui->setupUi ( this );
    this->updateTimer = new UpdateTimer();
    this->connectSignals();
    //ui->progressBar->setMaximum ( OverlayWidget::httpUpdateInterval );
    this->setMouseTracking ( true );
    this->moveToBottomRightEdge();
    this->setVisibleViewType ( LOGIN_VIEW );
}

void OverlayWidget::connectSignals() {
    connect ( this->updateTimer, SIGNAL ( tick ( int ) ), this, SLOT ( updateHttpResponse ( int ) ) );
    connect ( this->connection, SIGNAL ( requestFinished ( SessionResponse ) ), this, SLOT ( onSessionResponse ( SessionResponse ) ) );
    connect ( this->connection, SIGNAL ( requestFinished ( UnderstandingResponse ) ), this, SLOT ( onUnderstandingResponse ( UnderstandingResponse ) ) );
    connect ( this->connection, SIGNAL ( requestFinished ( LoggedInResponse ) ), this, SLOT ( onLoggedInResponse ( LoggedInResponse ) ) );
    connect ( ui->loginwidget, SIGNAL ( returnPressed() ), this, SLOT ( sessionLogin() ) );
    connect ( ui->loginwidget, SIGNAL ( exitButtonClicked() ), this, SLOT ( close() ) );
    connect ( ui->loginwidget, SIGNAL ( loginButtonClicked() ), this, SLOT ( sessionLogin() ) );
    connect ( ui->actionChangeSession, SIGNAL ( triggered ( bool ) ), this, SLOT ( showSessionIdForm() ) );
    connect ( ui->actionMakeTransparent, SIGNAL ( triggered ( bool ) ), this, SLOT ( makeTransparent ( bool ) ) );
    connect ( ui->actionFullscreen, SIGNAL ( triggered ( bool ) ), this, SLOT ( makeFullscreen ( bool ) ) );
    connect ( ui->actionSwitchView, SIGNAL ( triggered ( bool ) ), this, SLOT ( switchView ( bool ) ) );
    connect ( ui->actionExit, SIGNAL ( triggered ( bool ) ), this, SLOT ( close() ) );
}

OverlayWidget::~OverlayWidget() {
    delete this->connection;
    delete this->updateTimer;
}

const Ui::OverlayWidget*const OverlayWidget::getUi() {
    return this->ui;
}

void OverlayWidget::moveToBottomRightEdge() {
    this->resize ( QSize ( xSize+20, ( ySize*2 ) + 32 ) );
    int xPos = QApplication::desktop()->screenGeometry().width() - this->size().width() - 8;
    int yPos = QApplication::desktop()->screenGeometry().height() - this->size().height() - 8;
    this->move ( xPos, yPos );
}

void OverlayWidget::setVisibleViewType ( OverlayWidget::VisibileViewType type ) {
    switch ( type ) {
    case LOGIN_VIEW:
        ui->loginwidget->show();
        ui->bardiagramwidget->hide();
        ui->sessioninformationwidget->hide();
        ui->menuWidget->hide();
        ui->logodiagramwidget->hide();
        this->setWindowFlags (
            Qt::Window
            | Qt::FramelessWindowHint
            | Qt::WindowStaysOnTopHint
        );
        this->show();
        break;
    case BAR_VIEW:
        ui->loginwidget->hide();
        ui->bardiagramwidget->show();
        ui->sessioninformationwidget->show();
        ui->menuWidget->show();
        ui->logodiagramwidget->hide();
        this->setWindowFlags (
            Qt::Window
            | Qt::FramelessWindowHint
            | Qt::WindowStaysOnTopHint
            | Qt::X11BypassWindowManagerHint
        );
        this->show();
        break;
    case COLORED_LOGO_VIEW:
        ui->loginwidget->hide();
        ui->sessioninformationwidget->show();
        ui->bardiagramwidget->hide();
        ui->menuWidget->show();
        ui->logodiagramwidget->show();
        this->setWindowFlags (
            Qt::Window
            | Qt::FramelessWindowHint
            | Qt::WindowStaysOnTopHint
            | Qt::X11BypassWindowManagerHint
        );
        this->show();
        break;
    }
}

void OverlayWidget::onSessionResponse ( SessionResponse response ) {
    this->sessionId = response.sessionId();

    if ( ! this->sessionId.isNull() ) {
        this->setVisibleViewType ( BAR_VIEW );
        this->updateHttpResponse ( OverlayWidget::httpUpdateInterval );
        ui->sessioninformationwidget->updateSessionLabel ( response.shortName(), response.sessionId() );
        return;
    }
    this->makeTransparent ( false );
}

void OverlayWidget::onUnderstandingResponse ( UnderstandingResponse response ) {
    this->latestUnderstandingResponses = response.count();

    ui->bardiagramwidget->updateFromResponse ( response );
    ui->logodiagramwidget->updateFromResponse ( response );
}

void OverlayWidget::onLoggedInResponse ( LoggedInResponse response ) {
    this->loggedInUsers = response.value();
    ui->sessioninformationwidget->updateCounterLabel ( this->latestUnderstandingResponses, this->loggedInUsers );
}

void OverlayWidget::updateHttpResponse ( int ticks ) {
    ui->sessioninformationwidget->updateProgressBar ( ticks, OverlayWidget::httpUpdateInterval );
    if (
        ticks == OverlayWidget::httpUpdateInterval
        and ! this->sessionId.isEmpty()
    ) {
        this->connection->requestUnderstanding();
        this->connection->requestLoggedIn();
        this->updateTimer->reset();
    }
}

void OverlayWidget::sessionLogin() {
    this->connection->requestSession ( ui->loginwidget->text() );
    this->showQRCode ( QString ( "https://ars.thm.de/#id/" ) + ui->loginwidget->text() );
    this->moveToBottomRightEdge();
}

void OverlayWidget::makeTransparent ( bool enabled ) {
    ui->actionMakeTransparent->setChecked ( enabled );
    if ( enabled ) {
        this->setWindowOpacity ( .5 );
        return;
    }
    this->setWindowOpacity ( 1 );
}

void OverlayWidget::makeFullscreen ( bool enabled ) {
    if ( enabled ) {

        this->move ( 0,0 );
        this->setMaximumSize (
            QApplication::desktop()->screenGeometry().width(),
            QApplication::desktop()->screenGeometry().height()
        );
        this->resize (
            QApplication::desktop()->screenGeometry().width(),
            QApplication::desktop()->screenGeometry().height()
        );
        this->setWindowState ( this->windowState() ^ Qt::WindowFullScreen );
        this->show();
        return;
    }

    this->setWindowState ( this->windowState() & ~Qt::WindowFullScreen );
    this->show();

    this->moveToBottomRightEdge();
}

void OverlayWidget::showSessionIdForm() {
    this->makeTransparent ( false );
    this->setVisibleViewType ( LOGIN_VIEW );
    this->moveToBottomRightEdge();
}

void OverlayWidget::switchView ( bool coloredLogoView ) {
    if ( coloredLogoView ) {
        this->setVisibleViewType ( COLORED_LOGO_VIEW );
        return;
    }
    this->setVisibleViewType ( BAR_VIEW );
}

void OverlayWidget::showQRCode ( QString url ) {
    QRCodeWidget * qrcodewidget = new QRCodeWidget();
    qrcodewidget->showUrl ( QUrl ( url ) );
}
