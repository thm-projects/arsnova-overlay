#include <QtCore>
#include <QtGui>

#include "ui/overlaywidget.h"
#include "ui/mainwindow.h"
#include "svglogo.h"
#include "understandingresponse.h"
#include "httpconnection.h"
#include "ui/splashscreen.h"

#ifdef __APPLE__
extern "C" int startApplication ( int argc, char ** argv );
extern "C" int stopApplication();
#endif

int main ( int argc, char** argv ) {
#ifdef __APPLE__
    startApplication ( argc, argv );
#endif

    QApplication app ( argc, argv );
    app.setStyle ( "plastique" );

    SplashScreen::instance()->showMessage("Starting ARSnovawidget");
    SplashScreen::instance()->show();
    
    MainWindow mainWindow;
    mainWindow.show();
    
    OverlayWidget widget ( new HttpConnection() );
    widget.show();

#ifdef __APPLE__
    stopApplication();
#endif
    return app.exec();
}
