#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QtGui>
#include <atomic>
#include <mutex>

class SplashScreen : public QSplashScreen {

public:
    static SplashScreen * instance();
    static void destroy();
    void showMessage ( QString message );

private:
    explicit SplashScreen ( const QPixmap& pixmap = QPixmap(), Qt::WindowFlags f = 0 );
    static std::atomic<SplashScreen *> _instance;
};

#endif // SPLASHSCREEN_H
