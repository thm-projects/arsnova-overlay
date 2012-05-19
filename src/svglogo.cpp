#include "svglogo.h"

SvgLogo::SvgLogo() : file ( new QFile ( ":images/logo.svg" ) ) {
    this->file->open ( QIODevice::ReadOnly );
    this->plainContents = this->file->readAll();
    this->file->close();
    this->setColorValue ( -1 );
}

void SvgLogo::updateFromResponse ( UnderstandingResponse response ) {
    if ( response.values().size() != 4 ) return;

    float sum = 0;
    float all = 0;
    for ( int i = 0; i <= 3; i++ ) {
        all += response.values().at ( i ) * i;
        sum += response.values().at ( i );
    }

    if ( sum == 0 ) this->setColorValue ( -1 );
    this->setColorValue ( all/sum );
}

void SvgLogo::setColorValue ( float value ) {
    this->contents = this->plainContents;
    if ( value >= 0 and value < 1 ) {
        this->setColors ( qRgb ( 122, 184, 68 ), qRgb ( 254, 201, 41 ), value );
    } else if ( value >= 1 and value < 2 ) {
        this->setColors ( qRgb ( 254, 201, 41 ), qRgb ( 237, 96, 28 ), value - 1 );
    } else if ( value >= 2 and value <= 3 ) {
        this->setColors ( qRgb ( 237, 96, 28 ), qRgb ( 235, 235, 235 ), value - 2 );
    } else {
        this->setColors ( qRgb ( 48, 48, 48 ), qRgb ( 48, 48, 48 ), 1 );
    }
}

void SvgLogo::setColors ( QColor start, QColor end, float value ) {
    this->baseColor.setRed ( calculateColor ( start.red(), end.red(), value ) );
    this->baseColor.setGreen ( calculateColor ( start.green(), end.green(), value ) );
    this->baseColor.setBlue ( calculateColor ( start.blue(), end.blue(), value ) );

    QColor darkColor = this->baseColor.darker ( 120 );
    QColor lightColor = this->baseColor.lighter ( 120 );

    QString darkString = QString ( "#" )
                         + QString::number ( darkColor.red(),16 )
                         + QString::number ( darkColor.green(),16 )
                         + QString::number ( darkColor.blue(),16 );

    QString baseString = QString ( "#" )
                         + QString::number ( this->baseColor.red(),16 )
                         + QString::number ( this->baseColor.green(),16 )
                         + QString::number ( this->baseColor.blue(),16 );

    QString lightString = QString ( "#" )
                          + QString::number ( lightColor.red(),16 )
                          + QString::number ( lightColor.green(),16 )
                          + QString::number ( lightColor.blue(),16 );

    this->contents.replace ( "#5c861a", darkString.toUtf8() );
    this->contents.replace ( "#80ba24", baseString.toUtf8() );
    this->contents.replace ( "#afe060", lightString.toUtf8() );
}

int SvgLogo::calculateColor ( int start, int end, float value ) {
    if ( start >= end ) {
        return ( ( start - end ) * ( 1-value ) ) + end;
    } else {
        return ( ( end - start ) * value ) + start;
    }
}

QColor SvgLogo::color() {
    return this->baseColor;
}

QByteArray SvgLogo::toXml() {
    return this->contents;
}
