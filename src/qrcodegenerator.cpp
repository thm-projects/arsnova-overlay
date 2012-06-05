#include "qrcodegenerator.h"

QRCodeGenerator::QRCodeGenerator ( QString text ) {
    this->qrcode = QRcode_encodeString8bit ( text.toUtf8().data(), 0, QR_ECLEVEL_H );
}

QRCodeGenerator::~QRCodeGenerator() {
    QRcode_free ( this->qrcode );
}

QImage QRCodeGenerator::generate ( ) {
    QSize imageSize = QSize ( this->qrcode->width, this->qrcode->width );
    QImage image ( imageSize, QImage::Format_Mono );
    image.setColor ( 0, qRgb ( 0, 0, 0 ) );
    image.setColor ( 1, qRgb ( 255, 255, 255 ) );

    int index = 0;
    for ( int y = 0; y <= this->qrcode->width - 1; y++ ) {
        for ( int x = 0; x <= this->qrcode->width - 1; x++ ) {
            image.setPixel ( x,y, ( this->qrcode->data[index] & 1 ) ? 0 : 1 );
            index++;
        }
    }

    return image;
}
