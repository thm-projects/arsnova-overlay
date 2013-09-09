#ifndef ARSNOVAWIDGETCOLLECTION_H
#define ARSNOVAWIDGETCOLLECTION_H

#include <QtGui>
#include <QDesignerCustomWidgetCollectionInterface>

#include "loginwidgetplugin.h"
#include "bardiagramwidgetplugin.h"
#include "logodiagramwidgetplugin.h"
#include "emotediagramwidgetplugin.h"
#include "sessioninformationwidgetplugin.h"

class ArsNovaWidgetCollection : public QObject, QDesignerCustomWidgetCollectionInterface {
    Q_OBJECT
    Q_INTERFACES ( QDesignerCustomWidgetCollectionInterface )

public:
    explicit ArsNovaWidgetCollection ( QObject* parent = 0 );
    virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const;

private:
    QList<QDesignerCustomWidgetInterface*> widgets;
};

#endif // ARSNOVAWIDGETCOLLECTION_H
