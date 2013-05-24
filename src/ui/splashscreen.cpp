#include "splashscreen.h"

std::atomic<SplashScreen *> SplashScreen::_instance ( nullptr );

SplashScreen::SplashScreen ( const QPixmap& pixmap, Qt::WindowFlags f ) : QSplashScreen ( pixmap, f ) {

}

SplashScreen * SplashScreen::instance() {
    static std::mutex mutex;
    SplashScreen * splashScreen = _instance.load();
    if ( _instance == nullptr ) {
        std::lock_guard<std::mutex>  lock ( mutex );
        if ( _instance == nullptr ) {
            splashScreen = new SplashScreen ( QPixmap ( ":images/images/splash.png" ) );
            _instance.store ( splashScreen );
        }
    }
    return splashScreen;
}

void SplashScreen::destroy() {
    delete _instance.load();
}

void SplashScreen::showMessage ( QString message ) {
    QSplashScreen::show();
    QSplashScreen::showMessage ( message, Qt::AlignBottom|Qt::AlignLeft, Qt::gray );
}
