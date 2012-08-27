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
    StubConnection * connection;

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testShouldDisplayQRCodeWidget();
    void testShouldDisplayCorrectUrl();
    void testShouldDisplayCorrectUrlAfterSessionLogin();
};

#endif // QRCODEWIDGETTEST_H
