#ifndef SVGLOGO_H
#define SVGLOGO_H

#include <QtCore>
#include <QtGui>
#include <QtSvg>

#include <memory>

#include "understandingresponse.h"

class SvgLogo {

public:
    explicit SvgLogo();
    virtual ~SvgLogo();

    void updateFromResponse ( UnderstandingResponse response );
    QColor color();
    QByteArray toXml();


private:
    class SvgLogoPrivate;
    SvgLogoPrivate * _private;
};

#endif // SVGLOGO_H
