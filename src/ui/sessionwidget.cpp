#include "sessionwidget.h"

SessionWidget::SessionWidget ( SessionContext * context, QWidget* parent, Qt::WindowFlags f )
    : QWidget ( parent, f ), connection ( context->connection() ), _ui ( new Ui::SessionWidget() ) {
    _ui->setupUi ( this );

    connect ( this->connection, SIGNAL ( requestFinished ( UnderstandingResponse ) ), this, SLOT ( onUnderstandingResponse ( UnderstandingResponse ) ) );
}

const Ui::SessionWidget * const SessionWidget::getUi() {
    return this->_ui;
}

void SessionWidget::onUnderstandingResponse ( UnderstandingResponse response ) {
    _ui->bardiagramwidget->updateFromResponse ( response );
    _ui->logodiagramwidget->updateFromResponse ( response );
}
