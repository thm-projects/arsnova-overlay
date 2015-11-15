#include "svglogotest.h"

SvgLogoTest::SvgLogoTest ( QObject* parent ) : QObject ( parent ) {}

void SvgLogoTest::initTestCase() {
    this->svgLogo = new SvgLogo();
}

void SvgLogoTest::cleanupTestCase() {
    delete this->svgLogo;
}

void SvgLogoTest::testShouldShowGreenLogo() {
    this->svgLogo->updateFromResponse ( FeedbackResponse ( 10,0,0,0 ) );
    QCOMPARE ( this->svgLogo->color(), QColor ( qRgb ( 128, 187, 36 ) ) );
}

void SvgLogoTest::testShouldShowYellowLogo() {
    this->svgLogo->updateFromResponse ( FeedbackResponse ( 0,10,0,0 ) );
    QCOMPARE ( this->svgLogo->color(), QColor ( qRgb ( 242, 169, 0 ) ) );

    this->svgLogo->updateFromResponse ( FeedbackResponse ( 10,0,10,0 ) );
    QCOMPARE ( this->svgLogo->color(), QColor ( qRgb ( 242, 169, 0 ) ) );
}

void SvgLogoTest::testShouldShowRedLogo() {
    this->svgLogo->updateFromResponse ( FeedbackResponse ( 0,0,10,0 ) );
    QCOMPARE ( this->svgLogo->color(), QColor ( qRgb ( 151, 27, 47 ) ) );

    this->svgLogo->updateFromResponse ( FeedbackResponse ( 0,10,0,10 ) );
    QCOMPARE ( this->svgLogo->color(), QColor ( qRgb ( 151, 27, 47 ) ) );
}

void SvgLogoTest::testShouldShowGrayLogo() {
    this->svgLogo->updateFromResponse ( FeedbackResponse ( 0,0,0,10 ) );
    QCOMPARE ( this->svgLogo->color(), QColor ( qRgb ( 74, 92, 102 ) ) );
}
