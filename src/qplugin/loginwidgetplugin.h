#ifndef LOGINWIDGETPLUGIN_H
#define LOGINWIDGETPLUGIN_H

#include <QtGui>
#include <QDesignerCustomWidgetInterface>
#include "loginwidget.h"

class LoginWidgetPlugin
        : public QObject, public QDesignerCustomWidgetInterface {

    Q_OBJECT
    Q_INTERFACES ( QDesignerCustomWidgetInterface )

public:
    explicit LoginWidgetPlugin ( QObject * parent = 0 );

    QString name() const;
    QString includeFile() const;
    QString group() const;
    QIcon icon() const;
    QString toolTip() const;
    QString whatsThis() const;
    bool isContainer() const;
    QWidget * createWidget ( QWidget * parent );

};

#endif // LOGINWIDGETPLUGIN_H
