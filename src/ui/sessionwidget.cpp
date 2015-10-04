#include "sessionwidget.h"

SessionWidget::SessionWidget ( SessionContext * context, QWidget * parent, Qt::WindowFlags f )
    : QWidget ( parent, f ),
      _ui ( new Ui::SessionWidget() ),
      connection ( context->connection() ),
      context ( context ) {
    _ui->setupUi ( this );

    connect ( this->connection, SIGNAL ( requestFinished ( FeedbackResponse ) ), this, SLOT ( onUnderstandingResponse ( FeedbackResponse ) ) );
    connect ( this->connection, SIGNAL ( requestFinished ( SessionResponse ) ), this, SLOT ( onSessionResponse ( SessionResponse ) ) );
    connect ( _ui->sessionListWidget, SIGNAL ( sessionChanged ( QString ) ), this, SLOT ( onItemClicked ( QString ) ) );

    connect ( _ui->diagramRadioButton, SIGNAL ( clicked ( bool ) ), this, SLOT ( onViewModeChanged() ) );
    connect ( _ui->iconRadioButton, SIGNAL ( clicked ( bool ) ), this, SLOT ( onViewModeChanged() ) );
    connect ( _ui->emoteRadioButton, SIGNAL ( clicked ( bool ) ), this, SLOT ( onViewModeChanged() ) );

    connect ( _ui->bardiagramwidget, SIGNAL ( clicked ( bool ) ), this, SLOT ( onBarDiagramSelected() ) );
    connect ( _ui->logodiagramwidget, SIGNAL ( clicked ( bool ) ), this, SLOT ( onLogoDiagramSelected() ) );
    connect ( _ui->emotediagramwidget, SIGNAL ( clicked ( bool ) ), this, SLOT ( onEmoteDiagramSelected() ) );
}

SessionWidget::~SessionWidget() {
    delete _ui->bardiagramwidget;
    delete _ui->logodiagramwidget;
    delete _ui->emotediagramwidget;
    delete _ui;
}

const Ui::SessionWidget * const SessionWidget::getUi() {
    return this->_ui;
}

void SessionWidget::onUnderstandingResponse ( FeedbackResponse response ) {
    _ui->bardiagramwidget->updateFromResponse ( response );
    _ui->logodiagramwidget->updateFromResponse ( response );
    _ui->emotediagramwidget->updateFromResponse ( response );
}

void SessionWidget::onSessionResponse ( SessionResponse response ) {
    if ( ! this->context->isValid() || response.sessionId().isEmpty() ) return;

    QVariantMap newSession;
    newSession.insert ( "keyword", response.sessionId() );
    newSession.insert ( "name", response.name() );
    newSession.insert ( "shortName", response.shortName() );
    newSession.insert ( "active", true );

    _ui->sessionListWidget->addSession ( newSession );
}

void SessionWidget::onItemClicked ( QString sessionKey ) {
    this->connection->requestSession ( sessionKey );
}

void SessionWidget::onViewModeChanged() {
    if ( ! context->isValid() ) return;

    if ( _ui->diagramRadioButton->isChecked() ) {
        context->setViewType ( SessionContext::DIAGRAM_VIEW );
    } else if ( _ui->iconRadioButton->isChecked() ) {
        context->setViewType ( SessionContext::ICON_VIEW );
    } else if ( _ui->emoteRadioButton->isChecked() ) {
        context->setViewType ( SessionContext::EMOTE_VIEW );
    }
}

void SessionWidget::onBarDiagramSelected() {
    _ui->diagramRadioButton->setChecked ( true );
    this->onViewModeChanged();
}

void SessionWidget::onLogoDiagramSelected() {
    _ui->iconRadioButton->setChecked ( true );
    this->onViewModeChanged();
}

void SessionWidget::onEmoteDiagramSelected() {
    _ui->emoteRadioButton->setChecked ( true );
    this->onViewModeChanged();
}
