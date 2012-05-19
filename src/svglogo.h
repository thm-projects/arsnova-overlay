#ifndef SVGLOGO_H
#define SVGLOGO_H

#include <QtCore>
#include <QtGui>
#include <QtSvg>

#include "understandingresponse.h"

class SvgLogo {

public:
    explicit SvgLogo();
    
    void updateFromResponse(UnderstandingResponse response);
    QSvgWidget * widget();
    QColor color();


private:
    QFile * file;
    QByteArray contents;
    QSvgWidget * _widget;
    QColor baseColor;

    void setColorValue ( float value );
    void setColors ( QColor start, QColor end, float value );
    int calculateColor ( int start, int end, float value );
};

#endif // SVGLOGO_H
