#include "sessionwidget.h"

SessionWidget::SessionWidget ( SessionContext * context, QWidget * parent, Qt::WindowFlags f )
    : QWidget ( parent, f ), connection ( context->connection() ), _ui ( new Ui::SessionWidget() ) {
    _ui->setupUi ( this );

    connect ( this->connection, SIGNAL ( requestFinished ( UnderstandingResponse ) ), this, SLOT ( onUnderstandingResponse ( UnderstandingResponse ) ) );
    connect ( this->connection, SIGNAL ( requestFinished ( SessionResponse ) ), this, SLOT ( onSessionResponse ( SessionResponse ) ) );
}

const Ui::SessionWidget * const SessionWidget::getUi() {
    return this->_ui;
}

void SessionWidget::onUnderstandingResponse ( UnderstandingResponse response ) {
    _ui->bardiagramwidget->updateFromResponse ( response );
    _ui->logodiagramwidget->updateFromResponse ( response );
}

void SessionWidget::onSessionResponse ( SessionResponse response ) {
    QList<QTableWidgetItem *> items = _ui->tableWidget->findItems ( response.sessionId(), Qt::MatchExactly );
    if ( items.count() > 0 ) {
        items.at ( 0 )->setSelected ( true );
        return;
    }

    _ui->tableWidget->insertRow ( _ui->tableWidget->rowCount() );

    int newRow = _ui->tableWidget->rowCount()-1;
    _ui->tableWidget->selectRow ( newRow );

    _ui->tableWidget->setItem ( newRow, 0, new QTableWidgetItem ( response.shortName() ) );
    _ui->tableWidget->setItem ( newRow, 1, new QTableWidgetItem ( response.name() ) );
    _ui->tableWidget->setItem ( newRow, 2, new QTableWidgetItem ( response.sessionId() ) );
}
