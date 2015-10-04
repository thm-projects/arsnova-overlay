#include "overlaywidget.h"

#include "qrcodegenerator.h"

const int OverlayWidget::ySize = 160;
const int OverlayWidget::xSize = 160;

OverlayWidget::OverlayWidget ( SessionContext * context, QWidget * parent, Qt::WindowFlags f )
    : QWidget ( parent, f ),
      ui ( new Ui::OverlayWidget() ),
      connection ( context->connection() ),
      context ( context ) {
    ui->setupUi ( this );
    this->setAttribute ( Qt::WA_MacNoShadow, true );
    this->setAttribute ( Qt::WA_TranslucentBackground, true );
    this->setStyleSheet ( "background: rgba(128,128,128,16);" );

    this->moveToEdge ( Settings::instance()->screen() );

    this->latestUnderstandingResponses = 0;
    this->connectSignals();
    this->setMouseTracking ( true );
}

void OverlayWidget::connectSignals() {
    connect ( this->connection, SIGNAL ( requestFinished ( SessionResponse ) ), this, SLOT ( onSessionResponse ( SessionResponse ) ) );
    connect ( this->connection, SIGNAL ( requestFinished ( FeedbackResponse ) ), this, SLOT ( onFeedbackResponse ( FeedbackResponse ) ) );
    connect ( this->connection, SIGNAL ( requestFinished ( LoggedInResponse ) ), this, SLOT ( onLoggedInResponse ( LoggedInResponse ) ) );
    connect ( this->connection, SIGNAL ( requestFinished ( AudienceQuestionCountResponse ) ), this, SLOT ( onAudienceQuestionCountResponse ( AudienceQuestionCountResponse ) ) );
    connect ( ui->sessioninformationwidget, SIGNAL ( closeButtonClicked() ), this, SLOT ( close() ) );
    connect ( context, SIGNAL ( viewTypeChanged ( SessionContext::ViewType ) ), this, SLOT ( show() ) );
    connect ( Settings::instance().get(), SIGNAL ( settingsChanged() ), this, SLOT ( onSettingsChanged() ) );
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

void OverlayWidget::moveToEdge ( int screen ) {
    this->resize ( QSize ( xSize+20, ( ySize*2 ) + 32 ) );

    QRect screenGeometry = (
                               screen == -1 || screen > ( QApplication::desktop()->screenCount() - 1 )
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
        xPos = screenGeometry.x() + 8;
        yPos = screenGeometry.height() + screenGeometry.y() - this->size().height() - 8;
        break;
    case Settings::TOP_LEFT:
        xPos = screenGeometry.x() + 8;
        yPos = screenGeometry.y() + 8;
        break;
    case Settings::TOP_RIGHT:
        xPos = screenGeometry.width() + screenGeometry.x() - this->size().width() - 8;
        yPos = screenGeometry.y() + 8;
        break;
    }

    this->move ( xPos, yPos );
}

void OverlayWidget::setVisibleViewType ( SessionContext::ViewType type ) {
    if ( !context->isValid() ) return;

    switch ( type ) {
    case SessionContext::DIAGRAM_VIEW:
        ui->sessioninformationwidget->show();
        ui->bardiagramwidget->show();
        ui->logodiagramwidget->hide();
        ui->emotediagramwidget->hide();

        this->setWindowFlags (
            Qt::Window
            | Qt::FramelessWindowHint
            | Qt::NoDropShadowWindowHint
            | Qt::WindowStaysOnTopHint
            | Qt::X11BypassWindowManagerHint
        );
        break;
    case SessionContext::ICON_VIEW:
        ui->sessioninformationwidget->show();
        ui->bardiagramwidget->hide();
        ui->logodiagramwidget->show();
        ui->emotediagramwidget->hide();

        this->setWindowFlags (
            Qt::Window
            | Qt::FramelessWindowHint
            | Qt::NoDropShadowWindowHint
            | Qt::WindowStaysOnTopHint
            | Qt::X11BypassWindowManagerHint
        );
        break;
    case SessionContext::EMOTE_VIEW:
        ui->sessioninformationwidget->show();
        ui->bardiagramwidget->hide();
        ui->logodiagramwidget->hide();
        ui->emotediagramwidget->show();

        this->setWindowFlags (
            Qt::Window
            | Qt::FramelessWindowHint
            | Qt::NoDropShadowWindowHint
            | Qt::WindowStaysOnTopHint
            | Qt::X11BypassWindowManagerHint
        );
        break;
    }
}

void OverlayWidget::onSessionResponse ( SessionResponse response ) {
    this->sessionId = response.sessionId();

    if ( ! this->sessionId.isNull() ) {
        ui->sessioninformationwidget->updateSessionLabel ( response.shortName(), response.sessionId() );
        return;
    }
}

void OverlayWidget::onFeedbackResponse ( FeedbackResponse response ) {
    this->latestUnderstandingResponses = response.count();

    ui->bardiagramwidget->updateFromResponse ( response );
    ui->logodiagramwidget->updateFromResponse ( response );
    ui->emotediagramwidget->updateFromResponse ( response );

    this->repaint();
}

void OverlayWidget::onLoggedInResponse ( LoggedInResponse response ) {
    this->loggedInUsers = response.value();
    ui->sessioninformationwidget->updateCounterLabel ( this->latestUnderstandingResponses, this->loggedInUsers );
}

void OverlayWidget::onAudienceQuestionCountResponse ( AudienceQuestionCountResponse response ) {
    ui->sessioninformationwidget->updateAudienceQuestionCount ( response );
    this->repaint();
}

void OverlayWidget::onSettingsChanged() {
    this->moveToEdge ( Settings::instance()->screen() );
}

void OverlayWidget::paintEvent ( QPaintEvent * event ) {
    QPainter p ( this );
    p.setCompositionMode ( QPainter::CompositionMode_Clear );
    p.fillRect ( this->rect (), Qt::transparent );
    QWidget::paintEvent ( event );
}
