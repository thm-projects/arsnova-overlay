#ifndef OVERLAYWIDGETTEST_H
#define OVERLAYWIDGETTEST_H

#include <QtTest>
#include <QtTestGui>

#include "ui/overlaywidget.h"
#include "stubconnection.h"
#include "sessioncontext.h"

class OverlayWidgetTest : public QObject {

    Q_OBJECT

public:
    explicit OverlayWidgetTest ( QObject* parent = 0 );

private:
    OverlayWidget * overlayWidget;
    QRCodeWidget * qrCodeWidget;

    QSize widgetSize;
    SessionContext * context;

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testShouldShowOverlayWidget();
    void testShouldDisplayCorrectCountString();
    void testShouldSwitchToLogoDiagram();
    void testShouldSwitchToBarDiagram();
    void testShouldShowQRCodeWidget();
    void testShouldNotShowQRCodeWidget();
    void testShouldBeFullscreen();
    void testShouldNotBeFullscreen();
    void testShouldBeOpaque();
    void testShouldNotBeOpaque();
};

#endif // OVERLAYWIDGETTEST_H

