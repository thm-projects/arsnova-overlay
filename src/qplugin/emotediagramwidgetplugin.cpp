#include "emotediagramwidgetplugin.h"

EmoteDiagramWidgetPlugin::EmoteDiagramWidgetPlugin ( QObject* parent ) {}

QString EmoteDiagramWidgetPlugin::name() const {
    return "EmoteDiagramWidget";
}

QString EmoteDiagramWidgetPlugin::includeFile() const {
    return "qplugin/emotediagramwidget.h";
}

QString EmoteDiagramWidgetPlugin::group() const {
    return "ARSNova Widgets";
}

QIcon EmoteDiagramWidgetPlugin::icon() const {
    return QIcon ( ":/images/arsnova.svg" );
}

QString EmoteDiagramWidgetPlugin::toolTip() const {
    return "The ARSNova emote diagram widget";
}

QString EmoteDiagramWidgetPlugin::whatsThis() const {
    return "This Widget is a emote diagram widget for ARSNova";
}

bool EmoteDiagramWidgetPlugin::isContainer() const {
    return false;
}

QWidget* EmoteDiagramWidgetPlugin::createWidget ( QWidget * parent ) {
    return new LogoDiagramWidget ( parent );
}

//Q_EXPORT_PLUGIN2 ( emotediagramwidgetplugin, EmoteDiagramWidgetPlugin )
