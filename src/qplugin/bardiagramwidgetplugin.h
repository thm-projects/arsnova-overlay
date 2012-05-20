#ifndef BARDIAGRAMWIDGETPLUGIN_H
#define BARDIAGRAMWIDGETPLUGIN_H

#include <QtGui>
#include <QDesignerCustomWidgetInterface>

#include "bardiagramwidget.h"

class BarDiagramWidgetPlugin
        : public QObject, public QDesignerCustomWidgetInterface {

    Q_OBJECT
    Q_INTERFACES ( QDesignerCustomWidgetInterface )

public:
    explicit BarDiagramWidgetPlugin ( QObject * parent = 0 );

    QString name() const;
    QString includeFile() const;
    QString group() const;
    QIcon icon() const;
    QString toolTip() const;
    QString whatsThis() const;
    bool isContainer() const;
    QWidget * createWidget ( QWidget * parent );

};

#endif // BARDIAGRAMWIDGETPLUGIN_H
