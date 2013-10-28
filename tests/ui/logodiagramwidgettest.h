#ifndef LOGODIAGRAMWIDGETTEST_H
#define LOGODIAGRAMWIDGETTEST_H

#include <QtTest>
#include <QtTestGui>

#include "ui/logodiagramwidget.h"

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
    void testShouldScaleSvgWidget();
};

#endif // LOGODIAGRAMWIDGETTEST_H
