#include "overlaywidget.h"

const int OverlayWidget::ySize = 80;
const int OverlayWidget::xSize = 180;
const int OverlayWidget::httpUpdateInterval = 10;

OverlayWidget::OverlayWidget ( QWidget* parent, Qt::WindowFlags f )
    : QWidget ( parent, f ) , ui ( new Ui::OverlayWidget() ) {
    ui->setupUi ( this );

    this->updateTimer = new UpdateTimer();
    this->httpClient = new QHttp ( "ars.thm.de", QHttp::ConnectionModeHttps, 443 );
    this->httpConnection = new HttpConnection ( this->httpClient );

    this->svgLogo = new SvgLogo();

    connect ( this->updateTimer, SIGNAL ( tick ( int ) ), this, SLOT ( updateHttpResponse ( int ) ) );
    connect ( this->httpConnection, SIGNAL ( requestFinished ( SessionResponse ) ), this, SLOT ( onSessionResponse ( SessionResponse ) ) );
    connect ( this->httpConnection, SIGNAL ( requestFinished ( UnderstandingResponse ) ), this, SLOT ( onUnderstandingResponse ( UnderstandingResponse ) ) );
    connect ( this->httpConnection, SIGNAL ( requestFinished ( LoggedInResponse ) ), this, SLOT ( onLoggedInResponse ( LoggedInResponse ) ) );
    connect ( ui->loginwidget, SIGNAL ( editingFinished() ), this, SLOT ( sessionLogin() ) );
    connect ( ui->loginwidget, SIGNAL ( exitButtonClicked() ), this, SLOT ( close() ) );
    connect ( ui->loginwidget, SIGNAL ( loginButtonClicked() ), this, SLOT ( sessionLogin() ) );
    connect ( ui->actionChangeSession, SIGNAL ( triggered ( bool ) ), this, SLOT ( showSessionIdForm() ) );
    connect ( ui->actionMakeTransparent, SIGNAL ( triggered ( bool ) ), this, SLOT ( makeTransparent ( bool ) ) );
    connect ( ui->actionFullscreen, SIGNAL ( triggered ( bool ) ), this, SLOT ( makeFullscreen ( bool ) ) );
    connect ( ui->actionSwitchView, SIGNAL ( triggered ( bool ) ), this, SLOT ( switchView ( bool ) ) );
    connect ( ui->actionExit, SIGNAL ( triggered ( bool ) ), this, SLOT ( close() ) );

    this->setWindowFlags ( Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );

    ui->progressBar->setMaximum ( OverlayWidget::httpUpdateInterval );

    ui->logoWidget->hide();
    this->setMouseTracking ( true );

    this->moveToBottomRightEdge();
    this->setVisibleViewType ( LOGIN_VIEW );
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
        ui->onlineUsersLabel->hide();
        ui->progressBar->hide();
        ui->sessionNameLabel->hide();
        ui->menuWidget->hide();
        ui->logoWidget->hide();
        break;
    case BAR_VIEW:
        ui->loginwidget->hide();
        ui->onlineUsersLabel->show();
        ui->progressBar->show();
        ui->bardiagramwidget->show();
        ui->sessionNameLabel->show();
        ui->menuWidget->show();
        ui->logoWidget->hide();
        break;
    case COLORED_LOGO_VIEW:
        ui->loginwidget->hide();
        ui->onlineUsersLabel->show();
        ui->progressBar->show();
        ui->bardiagramwidget->hide();
        ui->sessionNameLabel->show();
        ui->menuWidget->show();
        ui->logoWidget->show();
        break;
    }
}

void OverlayWidget::onSessionResponse ( SessionResponse response ) {
    this->sessionId = response.sessionId();

    if ( ! this->sessionId.isNull() ) {
        this->setVisibleViewType ( BAR_VIEW );
        this->setWindowFlags ( Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint );
        this->show();
        this->updateHttpResponse ( OverlayWidget::httpUpdateInterval );
        ui->sessionNameLabel->setText (
            response.shortName()
            + "\n("
            + response.sessionId()
            + ")"
        );
        return;
    }
    this->makeTransparent ( false );
}

void OverlayWidget::onUnderstandingResponse ( UnderstandingResponse response ) {
    int values[4];
    for ( int i = 0; i <= 3; i++ ) {
        values[i] = response.values().at ( i );
    }

    this->latestUnderstandingResponses = values[0] + values[1] + values[2] + values[3];

    for ( int i = 0; i <= 3; i++ ) {
        if ( this->latestUnderstandingResponses > 0 ) {
            ui->bardiagramwidget->updateGraphicsBar ( i, ( values[i] * ySize ) / this->latestUnderstandingResponses );
        } else {
            ui->bardiagramwidget->updateGraphicsBar ( i, 0 );
        }
    }

    this->svgLogo->updateFromResponse ( response );
    ui->logoWidget->load ( this->svgLogo->toXml() );
}

void OverlayWidget::onLoggedInResponse ( LoggedInResponse response ) {
    this->loggedInUsers = response.value();
    ui->onlineUsersLabel->setText (
        QString ( "(" ) + QString::number ( this->latestUnderstandingResponses, 10 ) + "/"
        + QString::number ( this->loggedInUsers, 10 ) + ")"
    );
}

void OverlayWidget::updateHttpResponse ( int ticks ) {
    ui->progressBar->setValue ( ticks );
    if (
        ticks == OverlayWidget::httpUpdateInterval
        and ! this->sessionId.isEmpty()
    ) {
        this->httpConnection->requestUnderstanding();
        this->httpConnection->requestLoggedIn();
        this->updateTimer->reset();
    }
}

void OverlayWidget::sessionLogin() {
    this->httpConnection->requestSession ( ui->loginwidget->text() );
    this->makeTransparent ( true );
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
        this->setMaximumSize ( QApplication::desktop()->screenGeometry().width(),QApplication::desktop()->screenGeometry().height() );
        this->resize ( QApplication::desktop()->screenGeometry().width(),QApplication::desktop()->screenGeometry().height() );
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

    this->setWindowFlags ( Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );
    this->show();

    this->moveToBottomRightEdge();
}

void OverlayWidget::switchView ( bool coloredLogoView ) {
    if ( coloredLogoView ) {
        this->setVisibleViewType ( COLORED_LOGO_VIEW );
        return;
    }
    this->setVisibleViewType ( BAR_VIEW );
}
