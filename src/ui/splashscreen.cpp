#include "splashscreen.h"

SplashScreen * SplashScreen::_instance;

SplashScreen::SplashScreen ( const QPixmap& pixmap, Qt::WindowFlags f ) : QSplashScreen ( pixmap, f ) {
    this->setWindowFlags ( Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint );
}

SplashScreen * SplashScreen::instance() {
    if ( _instance == nullptr ) {
        _instance = new SplashScreen ( QPixmap ( ":images/images/splash.png" ) );
    }
    return _instance;
}

void SplashScreen::destroy() {
    if ( _instance != nullptr ) delete _instance;
}

void SplashScreen::showMessage ( QString message ) {
    QSplashScreen::show();
    QSplashScreen::showMessage ( message, Qt::AlignBottom|Qt::AlignLeft, Qt::gray );
}
