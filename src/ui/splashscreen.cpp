#include "splashscreen.h"

SplashScreen * SplashScreen::_instance = nullptr;

SplashScreen::SplashScreen ( const QPixmap& pixmap, Qt::WindowFlags f ) : QSplashScreen ( pixmap, f ) {

}

SplashScreen * SplashScreen::instance() {
    if ( _instance == nullptr ) {
        _instance = new SplashScreen ( QPixmap ( ":images/images/splash.png" ) );
    }
    return _instance;
}

void SplashScreen::showMessage ( QString message ) {
    QSplashScreen::show();
    QSplashScreen::showMessage ( message, Qt::AlignBottom|Qt::AlignLeft, Qt::gray );
}
