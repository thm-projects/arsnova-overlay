#ifndef LOGODIAGRAMWIDGETTEST_H
#define LOGODIAGRAMWIDGETTEST_H

#include <QtTest>
#include <QtTestGui>

#include "qplugin/logodiagramwidget.h"

class LogoDiagramWidgetTest : public QObject {

    Q_OBJECT

public:
    explicit LogoDiagramWidgetTest ( QObject* parent = 0 );

private:
    LogoDiagramWidget * logoDiagramWidget;

private slots:
    void initTestCase();
    void cleanupTestCase();
    
    void testShouldShowLogoDiagramWidget();
};

#endif // LOGODIAGRAMWIDGETTEST_H
