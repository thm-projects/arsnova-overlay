#include "bardiagramwidgetplugin.h"

BarDiagramWidgetPlugin::BarDiagramWidgetPlugin ( QObject* parent ) {}

QString BarDiagramWidgetPlugin::name() const {
    return "BarDiagramWidget";
}

QString BarDiagramWidgetPlugin::includeFile() const {
    return "qplugin/bardiagramwidget.h";
}

QString BarDiagramWidgetPlugin::group() const {
    return "ARSNova Widgets";
}

QIcon BarDiagramWidgetPlugin::icon() const {
    return QIcon ( ":/images/arsnova.svg" );
}

QString BarDiagramWidgetPlugin::toolTip() const {
    return "The ARSNova bar diagram widget";
}

QString BarDiagramWidgetPlugin::whatsThis() const {
    return "This Widget is a bar diagram widget for ARSNova";
}

bool BarDiagramWidgetPlugin::isContainer() const {
    return false;
}

QWidget* BarDiagramWidgetPlugin::createWidget ( QWidget * parent ) {
    return new BarDiagramWidget ( parent );
}

//Q_EXPORT_PLUGIN2 ( bardiagramwidgetplugin, BarDiagramWidgetPlugin )
