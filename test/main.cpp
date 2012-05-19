#include <QtCore>
#include <QtGui>
#include <QApplication>

#include "svglogotest.h"

int main ( int argc, char ** argv ) {
    QApplication app ( argc, argv );

    if ( QString ( argv[argc-1] ) == "SvgLogoTest" ) {
        SvgLogoTest svgLogoTest;
        return QTest::qExec ( &svgLogoTest, argc-1, argv );
    } else {
        qDebug() << "Not a valid test case selected. Add test case name as last parameter. (e.g.: tests -xunitxml SvgLogoTest)";
    }
}
