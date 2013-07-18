#ifndef EMOTEDIAGRAMWIDGETPLUGIN_H
#define EMOTEDIAGRAMWIDGETPLUGIN_H

#include <QtGui>
#include <QDesignerCustomWidgetInterface>

#include "emotediagramwidget.h"

class EmoteDiagramWidgetPlugin
        : public QObject, public QDesignerCustomWidgetInterface {

    Q_OBJECT
    Q_INTERFACES ( QDesignerCustomWidgetInterface )

public:
    explicit EmoteDiagramWidgetPlugin ( QObject * parent = 0 );

    QString name() const;
    QString includeFile() const;
    QString group() const;
    QIcon icon() const;
    QString toolTip() const;
    QString whatsThis() const;
    bool isContainer() const;
    QWidget * createWidget ( QWidget * parent );
};

#endif // EMOTEDIAGRAMWIDGETPLUGIN_H
