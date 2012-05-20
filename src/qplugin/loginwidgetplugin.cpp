#include "loginwidgetplugin.h"

LoginWidgetPlugin::LoginWidgetPlugin ( QObject* parent ) : QObject ( parent ) {}

QString LoginWidgetPlugin::name() const {
    return "LoginWidget";
}

QString LoginWidgetPlugin::includeFile() const {
    return "qplugin/loginwidget.h";
}

QString LoginWidgetPlugin::group() const {
    return "ARSNova Widgets";
}

QIcon LoginWidgetPlugin::icon() const {
    return QIcon ( ":/images/logo.svg" );
}

QString LoginWidgetPlugin::toolTip() const {
    return "The ARSNova login widget";
}

QString LoginWidgetPlugin::whatsThis() const {
    return "This Widget is a login widget for ARSNova";
}

bool LoginWidgetPlugin::isContainer() const {
    return false;
}

QWidget* LoginWidgetPlugin::createWidget ( QWidget * parent ) {
    return new LoginWidget ( parent );
}

//Q_EXPORT_PLUGIN2 ( loginwidgetplugin, LoginWidgetPlugin )
