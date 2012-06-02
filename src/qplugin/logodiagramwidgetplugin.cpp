#include "logodiagramwidgetplugin.h"

LogoDiagramWidgetPlugin::LogoDiagramWidgetPlugin ( QObject* parent ) {}

QString LogoDiagramWidgetPlugin::name() const {
    return "LogoDiagramWidget";
}

QString LogoDiagramWidgetPlugin::includeFile() const {
    return "qplugin/logodiagramwidget.h";
}

QString LogoDiagramWidgetPlugin::group() const {
    return "ARSNova Widgets";
}

QIcon LogoDiagramWidgetPlugin::icon() const {
    return QIcon ( ":/images/arsnova.svg" );
}

QString LogoDiagramWidgetPlugin::toolTip() const {
    return "The ARSNova logo diagram widget";
}

QString LogoDiagramWidgetPlugin::whatsThis() const {
    return "This Widget is a logo diagram widget for ARSNova";
}

bool LogoDiagramWidgetPlugin::isContainer() const {
    return false;
}

QWidget* LogoDiagramWidgetPlugin::createWidget ( QWidget * parent ) {
    return new LogoDiagramWidget ( parent );
}

//Q_EXPORT_PLUGIN2 ( logodiagramwidgetplugin, LogoDiagramWidgetPlugin )
