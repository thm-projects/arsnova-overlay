#include "sessioninformationwidgetplugin.h"

SessionInformationWidgetPlugin::SessionInformationWidgetPlugin ( QObject* parent )
    : QObject ( parent ) {}

QString SessionInformationWidgetPlugin::name() const {
    return "SessionInformationWidget";
}

QString SessionInformationWidgetPlugin::includeFile() const {
    return "qplugin/sessioninformationwidget.h";
}

QString SessionInformationWidgetPlugin::group() const {
    return "ARSNova Widgets";
}

QIcon SessionInformationWidgetPlugin::icon() const {
    return QIcon ( ":/images/arsnova.svg" );
}

QString SessionInformationWidgetPlugin::toolTip() const {
    return "The ARSNova session information widget";
}

QString SessionInformationWidgetPlugin::whatsThis() const {
    return "This Widget is a session information widget for ARSNova";
}

bool SessionInformationWidgetPlugin::isContainer() const {
    return false;
}

QWidget* SessionInformationWidgetPlugin::createWidget ( QWidget * parent ) {
    return new SessionInformationWidget ( parent );
}

//Q_EXPORT_PLUGIN2 ( sessioninformationwidgetplugin, SessionInformationWidgetPlugin )
