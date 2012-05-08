#include <QtCore>
#include <QtGui>

#include "ui/overlaywidget.h"

#ifdef __APPLE__
    extern "C" int startApplication(int argc, char ** argv);
    extern "C" int stopApplication();
#endif

int main ( int argc, char** argv ) {
    startApplication(argc, argv);
    QApplication app ( argc, argv );
       
    OverlayWidget widget;
    widget.show();
    
    stopApplication();
    return app.exec();
}
