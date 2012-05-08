#include <QtCore>
#include <QtGui>

#include "ui/overlaywidget.h"

#ifdef __APPLE__
extern "C" int startApplication ( int argc, char ** argv );
extern "C" int stopApplication();
#endif

int main ( int argc, char** argv ) {
#ifdef __APPLE__
    startApplication ( argc, argv );
#endif
    QApplication app ( argc, argv );

    OverlayWidget widget;
    widget.show();

#ifdef __APPLE__
    stopApplication();
#endif
    return app.exec();
}
