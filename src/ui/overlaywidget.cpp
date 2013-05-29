#include "overlaywidget.h"

#include "qrcodegenerator.h"

const int OverlayWidget::ySize = 80;
const int OverlayWidget::xSize = 180;
const int OverlayWidget::httpUpdateInterval = 10;

OverlayWidget::OverlayWidget ( SessionContext * context, QWidget * parent, Qt::WindowFlags f )
    : QWidget ( parent, f ),
      ui ( new Ui::OverlayWidget() ),
      connection ( context->connection() ),
      context ( context ) {
    ui->setupUi ( this );
    this->latestUnderstandingResponses = 0;
    this->updateTimer = new UpdateTimer();
    this->connectSignals();
    this->setMouseTracking ( true );
    this->moveToBottomRightEdge();
    this->setVisibleViewType ( SessionContext::DIAGRAM_VIEW );
}

void OverlayWidget::connectSignals() {
    connect ( this->updateTimer, SIGNAL ( tick ( int ) ), this, SLOT ( updateHttpResponse ( int ) ) );
    connect ( this->connection, SIGNAL ( requestFinished ( SessionResponse ) ), this, SLOT ( onSessionResponse ( SessionResponse ) ) );
    connect ( this->connection, SIGNAL ( requestFinished ( UnderstandingResponse ) ), this, SLOT ( onUnderstandingResponse ( UnderstandingResponse ) ) );
    connect ( this->connection, SIGNAL ( requestFinished ( LoggedInResponse ) ), this, SLOT ( onLoggedInResponse ( LoggedInResponse ) ) );
    connect ( ui->actionMakeTransparent, SIGNAL ( triggered ( bool ) ), this, SLOT ( makeTransparent ( bool ) ) );
    connect ( ui->actionExit, SIGNAL ( triggered ( bool ) ), this, SLOT ( close() ) );
    connect ( context, SIGNAL ( viewTypeChanged ( SessionContext::ViewType ) ), this, SLOT ( setVisibleViewType ( SessionContext::ViewType ) ) );
}

OverlayWidget::~OverlayWidget() {
    delete this->connection;
    delete this->updateTimer;
    delete this->ui;
}

void OverlayWidget::show() {
    this->setVisibleViewType ( context->viewType() );
    QWidget::show();
}

bool OverlayWidget::close() {
    return QWidget::close();
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

void OverlayWidget::setVisibleViewType ( SessionContext::ViewType type ) {
    if ( !context->isValid() ) return;
    switch ( type ) {
    case SessionContext::DIAGRAM_VIEW:
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
        break;
    case SessionContext::ICON_VIEW:
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
        break;
    }
    QWidget::show();
}

void OverlayWidget::onSessionResponse ( SessionResponse response ) {
    this->sessionId = response.sessionId();

    if ( ! this->sessionId.isNull() ) {
        this->setVisibleViewType ( context->viewType() );
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

void OverlayWidget::makeTransparent ( bool enabled ) {
    ui->actionMakeTransparent->setChecked ( enabled );
    if ( enabled ) {
        this->setWindowOpacity ( .5 );
        return;
    }
    this->setWindowOpacity ( 1 );
}
