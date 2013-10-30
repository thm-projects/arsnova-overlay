#ifndef BARDIAGRAMWIDGETTEST_H
#define BARDIAGRAMWIDGETTEST_H

#include <QtTest>
#include <QtTestGui>

#include "ui/bardiagramwidget.h"

class BarDiagramWidgetTest : public QObject {

    Q_OBJECT

public:
    explicit BarDiagramWidgetTest ( QObject* parent = 0 );

private:
    BarDiagramWidget * barDiagramWidget;

private slots:
    void initTestCase();
    void cleanupTestCase();
    
    void testShouldShowBarDiagramWidget();
};

#endif // BARDIAGRAMWIDGETTEST_H
