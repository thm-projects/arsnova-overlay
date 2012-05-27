#ifndef OVERLAYWIDGETTEST_H
#define OVERLAYWIDGETTEST_H

#include <QtTest>
#include <QtTestGui>

#include "ui/overlaywidget.h"

class OverlayWidgetTest : public QObject {

    Q_OBJECT

public:
    explicit OverlayWidgetTest ( QObject* parent = 0 );

private:
    OverlayWidget * overlayWidget;

private slots:
    void initTestCase();
    void cleanupTestCase();
    
    void testShouldShowOverlayWidget();
};

#endif // OVERLAYWIDGETTEST_H
