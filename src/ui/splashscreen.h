#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QtGui>

class SplashScreen : public QSplashScreen {

public:
    static SplashScreen * instance();
    void showMessage ( QString message );

private:
    explicit SplashScreen ( const QPixmap& pixmap = QPixmap(), Qt::WindowFlags f = 0 );
    static SplashScreen * _instance;
};

#endif // SPLASHSCREEN_H
