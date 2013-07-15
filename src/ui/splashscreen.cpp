#include "splashscreen.h"

std::shared_ptr<SplashScreen> SplashScreen::_instance;

SplashScreen::SplashScreen ( const QPixmap& pixmap, Qt::WindowFlags f ) : QSplashScreen ( pixmap, f ) {
    this->setWindowFlags ( Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint );
}

std::shared_ptr<SplashScreen> SplashScreen::instance() {
    if ( _instance.get() == nullptr ) {
        _instance = std::shared_ptr<SplashScreen> ( new SplashScreen ( QPixmap ( ":images/images/splash.png" ) ) );
    }
    return _instance;
}

void SplashScreen::destroy() {
    //delete _instance;
}

void SplashScreen::showMessage ( QString message ) {
    QSplashScreen::show();
    QSplashScreen::showMessage ( message, Qt::AlignBottom|Qt::AlignLeft, Qt::gray );
}
