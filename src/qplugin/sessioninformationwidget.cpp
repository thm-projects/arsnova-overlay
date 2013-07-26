#include "sessioninformationwidget.h"

SessionInformationWidget::SessionInformationWidget ( QWidget* parent, Qt::WindowFlags f ) {
    this->setSource ( QUrl ( "qrc:/qml/ui/sessioninformation.qml" ) );
    item = qobject_cast<QDeclarativeItem *> ( this->rootObject() );
}

SessionInformationWidget::~SessionInformationWidget() {
    delete item;
}

QGraphicsScene * const SessionInformationWidget::getUi() {
    return item->scene();
}

void SessionInformationWidget::updateCounterLabel ( int feedback, int onlineUsers ) {
    item->setProperty ( "feedbackCount", feedback );
    item->setProperty ( "userCount", onlineUsers );
}

void SessionInformationWidget::updateProgressBar ( int value, int max ) {

}

void SessionInformationWidget::updateSessionLabel ( QString sessionName, QString sessionID ) {

}

void SessionInformationWidget::updateAudienceQuestionCount ( AudienceQuestionCountResponse response ) {
    item->setProperty ( "unreadMessages", response.read() );
}
