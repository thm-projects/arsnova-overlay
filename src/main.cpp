#include <QtCore>
#include <QtGui>

#include "ui/overlaywidget.h"

int main ( int argc, char** argv ) {
    QApplication app ( argc, argv );
       
    OverlayWidget widget;
    widget.show();
    
    return app.exec();
}
