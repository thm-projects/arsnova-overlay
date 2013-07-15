#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QtGui>
#include <memory>

class SplashScreen : public QSplashScreen {

public:
    static std::shared_ptr<SplashScreen> instance();
    static void destroy();
    void showMessage ( QString message );

private:
    explicit SplashScreen ( const QPixmap& pixmap = QPixmap(), Qt::WindowFlags f = 0 );
    static std::shared_ptr<SplashScreen> _instance;
};

#endif // SPLASHSCREEN_H
