#include "loginwidget.h"
#include "version.h"

LoginWidget::LoginWidget ( QWidget* parent, Qt::WindowFlags f ) {
    this->setSource ( QUrl ( "qrc:/qml/ui/login.qml" ) );
    item = qobject_cast<QDeclarativeItem *> ( this->rootObject() );
    connect ( item, SIGNAL ( loginButtonClick() ), this, SLOT ( on_loginButton_clicked() ) );
    connect ( item, SIGNAL ( exitButtonClick() ), this, SLOT ( on_exitButton_clicked() ) );

    QDeclarativeItem * dItem = item->findChild<QDeclarativeItem *> ( "versionstring" );
    if ( dItem != nullptr ) {
        dItem->setProperty (
            "text",
            QString ( "ARSnova Overlay" )
            + " " + VERSION_MAJOR
            + "." + VERSION_MINOR
            + "." + VERSION_PATCH );
    }
}

LoginWidget::~LoginWidget() {
    delete item;
}

QGraphicsScene * const LoginWidget::getUi() {
    return this->scene();
}

QString LoginWidget::text() {
    QDeclarativeItem * dItem = item->findChild<QDeclarativeItem *> ( "sessionIdTextInput" );
    if ( dItem != nullptr ) {
        return dItem->property ( "text" ).toString();
    }
}

void LoginWidget::setText ( QString text ) {
    QDeclarativeItem * dItem = item->findChild<QDeclarativeItem *> ( "sessionIdTextInput" );
    if ( dItem != nullptr ) {
        dItem->setProperty ( "text", text );
    }
}

void LoginWidget::clear() {
    QDeclarativeItem * dItem = item->findChild<QDeclarativeItem *> ( "sessionIdTextInput" );
    if ( dItem != nullptr ) {
        dItem->setProperty ( "text", "" );
    }
}

void LoginWidget::on_exitButton_clicked() {
    emit this->exitButtonClicked();
}

void LoginWidget::on_loginButton_clicked() {
    emit this->loginButtonClicked();
}
