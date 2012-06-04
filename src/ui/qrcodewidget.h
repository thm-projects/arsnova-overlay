#ifndef QRCODEWIDGET_H
#define QRCODEWIDGET_H

#include <QtGui>
#include "ui_qrcodewidget.h"
#include "qrcodegenerator.h"

class QRCodeWidget : public QWidget, Ui::QRCodeWidget {
    Q_OBJECT

public:
    explicit QRCodeWidget ( QWidget* parent = 0, Qt::WindowFlags f = 0 );
    void showUrl ( QUrl url );

private:
    Ui::QRCodeWidget * _ui;
    void adjustSize();
    QSize neededQRCodeSize();
};

#endif // QRCODEWIDGET_H
