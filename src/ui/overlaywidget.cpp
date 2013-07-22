#include "overlaywidget.h"

#include "qrcodegenerator.h"

const int OverlayWidget::ySize = 80;
const int OverlayWidget::xSize = 180;
const int OverlayWidget::httpUpdateInterval = 3;

OverlayWidget::OverlayWidget ( SessionContext * context, QWidget * parent, Qt::WindowFlags f )
    : QWidget ( parent, f ),
      ui ( new Ui::OverlayWidget() ),
      connection ( context->connection() ),
      context ( context ) {
    ui->setupUi ( this );
    this->latestUnderstandingResponses = 0;
    this->connectSignals();
    this->setMouseTracking ( true );
    this->moveToBottomRightEdge();
}

void OverlayWidget::connectSignals() {
    connect ( this->context->updateTimer(), SIGNAL ( tick ( int ) ), this, SLOT ( updateHttpResponse ( int ) ) );
    connect ( this->connection, SIGNAL ( requestFinished ( SessionResponse ) ), this, SLOT ( onSessionResponse ( SessionResponse ) ) );
    connect ( this->connection, SIGNAL ( requestFinished ( FeedbackResponse ) ), this, SLOT ( onFeedbackResponse ( FeedbackResponse ) ) );
    connect ( this->connection, SIGNAL ( requestFinished ( LoggedInResponse ) ), this, SLOT ( onLoggedInResponse ( LoggedInResponse ) ) );
    connect ( ui->actionMakeTransparent, SIGNAL ( triggered ( bool ) ), this, SLOT ( makeTransparent ( bool ) ) );
    connect ( ui->actionExit, SIGNAL ( triggered ( bool ) ), this, SLOT ( close() ) );
    connect ( context, SIGNAL ( viewTypeChanged ( SessionContext::ViewType ) ), this, SLOT ( setVisibleViewType ( SessionContext::ViewType ) ) );
}

OverlayWidget::~OverlayWidget() {
    delete this->connection;
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

void OverlayWidget::moveToBottomRightEdge ( int screen ) {
    this->resize ( QSize ( xSize+20, ( ySize*2 ) + 32 ) );

    QRect screenGeometry = (
                               screen == -1
                               ? QApplication::desktop()->availableGeometry ( QApplication::desktop()->screenCount() - 1 )
                               : QApplication::desktop()->availableGeometry ( screen )
                           );

    int xPos = 8;
    int yPos = 8;

    switch ( Settings::instance()->widgetPosition() ) {
    case Settings::BOTTOM_RIGHT:
        xPos = screenGeometry.width() + screenGeometry.x() - this->size().width() - 8;
        yPos = screenGeometry.height() + screenGeometry.y() - this->size().height() - 8;
        break;
    case Settings::BOTTOM_LEFT:
        yPos = screenGeometry.height() + screenGeometry.y() - this->size().height() - 8;
        break;
    case Settings::TOP_LEFT:
        // No
        break;
    case Settings::TOP_RIGHT:
        xPos = screenGeometry.width() + screenGeometry.x() - this->size().width() - 8;
        break;
    }


    this->move ( xPos, yPos );
}

void OverlayWidget::setVisibleViewType ( SessionContext::ViewType type ) {
    if ( !context->isValid() ) return;
    switch ( type ) {
    case SessionContext::DIAGRAM_VIEW:
        ui->sessioninformationwidget->show();
        ui->menuWidget->show();

        ui->bardiagramwidget->show();
        ui->logodiagramwidget->hide();
        ui->emotediagramwidget->hide();

        this->setWindowFlags (
            Qt::Window
            | Qt::FramelessWindowHint
            | Qt::WindowStaysOnTopHint
            | Qt::X11BypassWindowManagerHint
        );
        break;
    case SessionContext::ICON_VIEW:
        ui->sessioninformationwidget->show();
        ui->menuWidget->show();

        ui->bardiagramwidget->hide();
        ui->logodiagramwidget->show();
        ui->emotediagramwidget->hide();

        this->setWindowFlags (
            Qt::Window
            | Qt::FramelessWindowHint
            | Qt::WindowStaysOnTopHint
            | Qt::X11BypassWindowManagerHint
        );
        break;
    case SessionContext::EMOTE_VIEW:
        ui->sessioninformationwidget->show();
        ui->menuWidget->show();

        ui->bardiagramwidget->hide();
        ui->logodiagramwidget->hide();
        ui->emotediagramwidget->show();

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
        this->updateHttpResponse ( OverlayWidget::httpUpdateInterval );
        ui->sessioninformationwidget->updateSessionLabel ( response.shortName(), response.sessionId() );
        return;
    }
    this->makeTransparent ( false );
}

void OverlayWidget::onFeedbackResponse ( FeedbackResponse response ) {
    this->latestUnderstandingResponses = response.count();

    ui->bardiagramwidget->updateFromResponse ( response );
    ui->logodiagramwidget->updateFromResponse ( response );
    ui->emotediagramwidget->updateFromResponse ( response );
}

void OverlayWidget::onLoggedInResponse ( LoggedInResponse response ) {
    this->loggedInUsers = response.value();
    ui->sessioninformationwidget->updateCounterLabel ( this->latestUnderstandingResponses, this->loggedInUsers );
}

void OverlayWidget::updateHttpResponse ( int ticks ) {
    ui->sessioninformationwidget->updateProgressBar ( ticks, OverlayWidget::httpUpdateInterval );
    if (
        ticks == OverlayWidget::httpUpdateInterval
        && ! this->sessionId.isEmpty()
    ) {
        this->connection->requestFeedback();
        this->connection->requestActiveUserCount();
        this->context->updateTimer()->reset();
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
