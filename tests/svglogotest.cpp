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
    QCOMPARE ( this->svgLogo->color(), QColor ( qRgb ( 122, 184, 68 ) ) );
}

void SvgLogoTest::testShouldShowYellowLogo() {
    this->svgLogo->updateFromResponse ( FeedbackResponse ( 0,10,0,0 ) );
    QCOMPARE ( this->svgLogo->color(), QColor ( qRgb ( 254, 201, 41 ) ) );

    this->svgLogo->updateFromResponse ( FeedbackResponse ( 10,0,10,0 ) );
    QCOMPARE ( this->svgLogo->color(), QColor ( qRgb ( 254, 201, 41 ) ) );
}

void SvgLogoTest::testShouldShowRedLogo() {
    this->svgLogo->updateFromResponse ( FeedbackResponse ( 0,0,10,0 ) );
    QCOMPARE ( this->svgLogo->color(), QColor ( qRgb ( 237, 96, 28 ) ) );

    this->svgLogo->updateFromResponse ( FeedbackResponse ( 0,10,0,10 ) );
    QCOMPARE ( this->svgLogo->color(), QColor ( qRgb ( 237, 96, 28 ) ) );
}

void SvgLogoTest::testShouldShowGrayLogo() {
    this->svgLogo->updateFromResponse ( FeedbackResponse ( 0,0,0,10 ) );
    QCOMPARE ( this->svgLogo->color(), QColor ( qRgb ( 235, 235, 235 ) ) );
}

void SvgLogoTest::testShouldShowMiddleGreenYellowLogo() {
    this->svgLogo->updateFromResponse ( FeedbackResponse ( 10,10,0,0 ) );
    QCOMPARE ( this->svgLogo->color(), QColor ( qRgb ( 188, 192, 54 ) ) );
}

