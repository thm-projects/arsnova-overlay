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

    int index = 0;
    for ( int y = 0; y <= this->qrcode->width - 1; y++ ) {
        for ( int x = 0; x <= this->qrcode->width - 1; x++ ) {
#ifdef __APPLE__
            image.setPixel ( x,y, ( this->qrcode->data[index] & 1 ) ? 1 : 0 );
#else
            image.setPixel ( x,y, ( this->qrcode->data[index] & 1 ) ? 0 : 1 );
#endif
            index++;
        }
    }

    return image;
}
