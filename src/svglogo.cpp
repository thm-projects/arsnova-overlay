#include "svglogo.h"

// SvgLogoPrivate

class SvgLogo::SvgLogoPrivate {
public:
    explicit SvgLogoPrivate ( std::shared_ptr< QFile > file ) : file ( file ) {
        this->file->open ( QIODevice::ReadOnly );
        this->plainContents = this->file->readAll();
        this->file->close();
        this->setColorValue ( -1 );
    };

    virtual ~SvgLogoPrivate() {}

    void setColorValue ( float value ) {
        this->_contents = this->plainContents;
        if ( value >= 0 and value < 1 ) {
            this->setColors ( qRgb ( 128, 187, 36 ), qRgb ( 242, 169, 0 ), value );
        } else if ( value >= 1 and value < 2 ) {
            this->setColors ( qRgb ( 242, 169, 0 ), qRgb ( 151, 27, 47 ), value - 1 );
        } else if ( value >= 2 and value <= 3 ) {
            this->setColors ( qRgb ( 151, 27, 47 ), qRgb ( 74, 92, 102 ), value - 2 );
        } else {
            this->setColors ( qRgb ( 74, 92, 102 ), qRgb ( 74, 92, 102 ), 1 );
        }
    }

    void setColors ( QColor start, QColor end, float value ) {
        this->_baseColor.setRed ( calculateColor ( start.red(), end.red(), value ) );
        this->_baseColor.setGreen ( calculateColor ( start.green(), end.green(), value ) );
        this->_baseColor.setBlue ( calculateColor ( start.blue(), end.blue(), value ) );

        QString baseString = QString ( "#" )
                             + QString::number ( this->_baseColor.red(), 16 ).rightJustified(2, '0')
                             + QString::number ( this->_baseColor.green(), 16 ).rightJustified(2, '0')
                             + QString::number ( this->_baseColor.blue(), 16 ).rightJustified(2, '0');

        this->_contents.replace ( "#000", baseString.toUtf8() );
    }

    int calculateColor ( int start, int end, float value ) {
        if ( start >= end ) {
            return ( ( start - end ) * ( 1-value ) ) + end;
        } else {
            return ( ( end - start ) * value ) + start;
        }
    }

    QColor baseColor() {
        return this->_baseColor;
    }

    QByteArray contents() {
        return _contents;
    }

private:
    std::shared_ptr< QFile > file;
    QByteArray _contents;
    QByteArray plainContents;
    QColor _baseColor;
};

SvgLogo::SvgLogo()
    : _private ( std::unique_ptr< SvgLogoPrivate > ( new SvgLogo::SvgLogoPrivate ( std::shared_ptr<QFile> ( new QFile ( ":images/arsnova-color.svg" ) ) ) ) ) {}

SvgLogo::~SvgLogo() {}

void SvgLogo::updateFromResponse ( FeedbackResponse response ) {
    if ( response.values().size() != 4 ) return;

    float sum = 0;
    float all = 0;
    for ( int i = 0; i <= 3; i++ ) {
        all += response.values().at ( i ) * i;
        sum += response.values().at ( i );
    }

    if ( sum == 0 ) _private->setColorValue ( -1 );
    _private->setColorValue ( all/sum );
}

QColor SvgLogo::color() {
    return _private->baseColor();
}

QByteArray SvgLogo::toXml() {
    return _private->contents();
}
