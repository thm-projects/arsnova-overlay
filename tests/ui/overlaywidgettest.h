#ifndef OVERLAYWIDGETTEST_H
#define OVERLAYWIDGETTEST_H

#include <QtTest>
#include <QtTestGui>

#include "ui/overlaywidget.h"
#include "stubconnection.h"

class OverlayWidgetTest : public QObject {

    Q_OBJECT

public:
    explicit OverlayWidgetTest ( QObject* parent = 0 );

private:
    OverlayWidget * overlayWidget;
    void enterSessionId ( QLineEdit * lineEdit );

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testShouldShowOverlayWidget();
    void testShouldNotDisplayBarDiagramWithoutSessionLogin();
    void testShouldDisplayBarDiagramAfterSessionLogin();
    void testShouldDisplayCorrectCountString();
    void testShouldSwitchToLogoDiagram();
    void testShouldSwitchToBarDiagram();
    void testShouldSwitchToLogin();
};

#endif // OVERLAYWIDGETTEST_H
