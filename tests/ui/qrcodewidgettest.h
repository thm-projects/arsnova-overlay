#ifndef QRCODEWIDGETTEST_H
#define QRCODEWIDGETTEST_H

#include <QtTest>
#include <QtTestGui>
#include "ui/qrcodewidget.h"

class QRCodeWidgetTest : public QObject {
    Q_OBJECT

public:
    explicit QRCodeWidgetTest ( QObject * parent = 0 );
    QRCodeWidget * qrCodeWidget;

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testShouldDisplayQRCodeWidget();
    void testShouldDisplayCorrectUrl();
};

#endif // QRCODEWIDGETTEST_H
