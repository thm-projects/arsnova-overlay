#ifndef QRCODEWIDGET_H
#define QRCODEWIDGET_H

#include <QtGui>
#include "ui_qrcodewidget.h"
#include "qrcodegenerator.h"

class QRCodeWidget : public QWidget, Ui::QRCodeWidget {
    Q_OBJECT

public:
    explicit QRCodeWidget ( QWidget* parent = 0, Qt::WindowFlags f = 0 );
    void setUrl ( QUrl url );
    const Ui::QRCodeWidget * const getUi();

private:
    Ui::QRCodeWidget * _ui;
    void adjustSize();
    QSize neededQRCodeSize();
    QString neededFontSize();
};

#endif // QRCODEWIDGET_H
