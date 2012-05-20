#ifndef LOGODIAGRAMWIDGETPLUGIN_H
#define LOGODIAGRAMWIDGETPLUGIN_H

#include <QtGui>
#include <QDesignerCustomWidgetInterface>

#include "logodiagramwidget.h"

class LogoDiagramWidgetPlugin
        : public QObject, public QDesignerCustomWidgetInterface {

    Q_OBJECT
    Q_INTERFACES ( QDesignerCustomWidgetInterface )

public:
    explicit LogoDiagramWidgetPlugin ( QObject * parent = 0 );

    QString name() const;
    QString includeFile() const;
    QString group() const;
    QIcon icon() const;
    QString toolTip() const;
    QString whatsThis() const;
    bool isContainer() const;
    QWidget * createWidget ( QWidget * parent );

};

#endif // LOGODIAGRAMWIDGETPLUGIN_H
