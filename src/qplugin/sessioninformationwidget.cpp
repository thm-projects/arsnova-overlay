#include "sessioninformationwidget.h"

SessionInformationWidget::SessionInformationWidget ( QWidget* parent, Qt::WindowFlags f )
    : QWidget ( parent ), _ui ( new Ui::SessionInformationWidget ) {
    _ui->setupUi ( this );
}

const Ui::SessionInformationWidget*const SessionInformationWidget::getUi() {
    return _ui;
}

void SessionInformationWidget::updateCounterLabel ( int feedback, int onlineUsers ) {
    _ui->onlineUsersLabel->setText (
        QString ( "(" ) + QString::number ( feedback, 10 )
        + "/"
        + QString::number ( onlineUsers, 10 ) + ")"
    );
}

void SessionInformationWidget::updateProgressBar ( int value, int max ) {
    _ui->progressBar->setMaximum ( max );
    _ui->progressBar->setValue ( value );
}

void SessionInformationWidget::updateSessionLabel ( QString sessionName, QString sessionID ) {
    _ui->sessionNameLabel->setText ( sessionID );
}
