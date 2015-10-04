#include "sessionlistwidget.h"

SessionListWidget::SessionListWidget ( QWidget* parent ) : QDeclarativeView ( parent ) {
    this->setSource ( QUrl ( "qrc:/qml/ui/sessionlist.qml" ) );
    item = qobject_cast<QDeclarativeItem *> ( this->rootObject() );

    connect ( item, SIGNAL ( sessionChanged ( QString ) ), this, SLOT ( onSessionChanged ( QString ) ) );
}

void SessionListWidget::addSession ( QVariantMap newSession ) {
    QMetaObject::invokeMethod (
        this->rootObject(),
        "append",
        Q_ARG ( QVariant, QVariant::fromValue ( newSession ) )
    );
}

void SessionListWidget::onSessionChanged ( QString sessionKey ) {
    emit this->sessionChanged ( sessionKey );
}
