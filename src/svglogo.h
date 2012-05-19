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
    QColor color();
    QByteArray toXml();


private:
    QFile * file;
    QByteArray contents;
    QByteArray plainContents;
    QColor baseColor;

    void setColorValue ( float value );
    void setColors ( QColor start, QColor end, float value );
    int calculateColor ( int start, int end, float value );
};

#endif // SVGLOGO_H
