#include "arsnovawidgetcollection.h"

ArsNovaWidgetCollection::ArsNovaWidgetCollection ( QObject* parent ) : QObject ( parent ) {
    this->widgets.append ( new LoginWidgetPlugin ( this ) );
    this->widgets.append ( new BarDiagramWidgetPlugin ( this ) );
}

QList< QDesignerCustomWidgetInterface* > ArsNovaWidgetCollection::customWidgets() const {
    return this->widgets;
}

Q_EXPORT_PLUGIN2 ( arsnovawidgetcollection, ArsNovaWidgetCollection )
