#ifndef SVGLOGO_H
#define SVGLOGO_H

#include <QtWidgets>
#include <QtSvg>

#include <memory>

#include "feedbackresponse.h"

class SvgLogo {

public:
    explicit SvgLogo();
    virtual ~SvgLogo();

    void updateFromResponse ( FeedbackResponse response );
    QColor color();
    QByteArray toXml();


private:
    class SvgLogoPrivate;
    std::unique_ptr< SvgLogoPrivate > _private;
};

#endif // SVGLOGO_H
