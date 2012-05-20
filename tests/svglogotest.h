#ifndef SVGLOGOTEST_H
#define SVGLOGOTEST_H

#include <QtTest>

#include "svglogo.h"
#include "understandingresponse.h"

class SvgLogoTest : public QObject {

    Q_OBJECT

public:
    explicit SvgLogoTest ( QObject * parent = nullptr );

private:
    SvgLogo * svgLogo;

private slots:
    void initTestCase();
    void cleanupTestCase();
    
    void testShouldShowGreenLogo();
    void testShouldShowYellowLogo();
    void testShouldShowRedLogo();
    void testShouldShowGrayLogo();
    
    void testShouldShowMiddleGreenYellowLogo();
};

#endif // SVGLOGOTEST_H
