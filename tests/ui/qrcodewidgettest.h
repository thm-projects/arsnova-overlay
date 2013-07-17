#ifndef QRCODEWIDGETTEST_H
#define QRCODEWIDGETTEST_H

#include <QtTest>
#include <QtTestGui>
#include "ui/qrcodewidget.h"
#include "stubconnection.h"

class QRCodeWidgetTest : public QObject {
    Q_OBJECT

public:
    explicit QRCodeWidgetTest ( QObject * parent = 0 );

private:
    QRCodeWidget * qrCodeWidget;
    QStackedWidget * stackedWidget;
    StubConnection * connection;

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testShouldDisplayCorrectUrl();
    void testShouldDisplayCorrectUrlAfterSessionLogin();
    void testShouldSwitchToFullscreenMode();
    void testShouldSelectAllTransformationModes();
};

#endif // QRCODEWIDGETTEST_H
