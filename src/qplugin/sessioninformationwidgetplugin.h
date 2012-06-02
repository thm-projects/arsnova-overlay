#ifndef SESSIONINFORMATIONWIDGETPLUGIN_H
#define SESSIONINFORMATIONWIDGETPLUGIN_H

#include <QtGui>
#include <QDesignerCustomWidgetInterface>
#include "sessioninformationwidget.h"

class SessionInformationWidgetPlugin
        : public QObject, public QDesignerCustomWidgetInterface {

    Q_OBJECT
    Q_INTERFACES ( QDesignerCustomWidgetInterface )

public:
    explicit SessionInformationWidgetPlugin ( QObject * parent = 0 );
    QString name() const;
    QString includeFile() const;
    QString group() const;
    QIcon icon() const;
    QString toolTip() const;
    QString whatsThis() const;
    bool isContainer() const;
    QWidget * createWidget ( QWidget * parent );
};

#endif // SESSIONINFORMATIONWIDGETPLUGIN_H
