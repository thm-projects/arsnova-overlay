#include "arsnovawidgetcollection.h"

ArsNovaWidgetCollection::ArsNovaWidgetCollection ( QObject* parent ) : QObject ( parent ) {
    this->widgets.append ( new LoginWidgetPlugin ( this ) );
    this->widgets.append ( new BarDiagramWidgetPlugin ( this ) );
    this->widgets.append ( new LogoDiagramWidgetPlugin ( this ) );
    this->widgets.append ( new EmoteDiagramWidgetPlugin ( this ) );
    this->widgets.append ( new SessionInformationWidgetPlugin ( this ) );
}

QList< QDesignerCustomWidgetInterface* > ArsNovaWidgetCollection::customWidgets() const {
    return this->widgets;
}

Q_EXPORT_PLUGIN2 ( arsnovawidgetcollection, ArsNovaWidgetCollection )
