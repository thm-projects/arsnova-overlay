#ifndef QRCODEGENERATOR_H
#define QRCODEGENERATOR_H

#include <QtGui>
#include <qrencode.h>

class QRCodeGenerator {

public:
    explicit QRCodeGenerator ( QString text );
    ~QRCodeGenerator();
    QImage generate ();

private:
    QRcode * qrcode;
};

#endif // QRCODEGENERATOR_H
