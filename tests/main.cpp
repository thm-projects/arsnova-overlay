#include <QtCore>
#include <QtGui>
#include <QApplication>

#include "svglogotest.h"
#include "qplugin/loginwidgettest.h"
#include "qplugin/bardiagramwidgettest.h"
#include "qplugin/logodiagramwidgettest.h"
#include "ui/overlaywidgettest.h"

int main ( int argc, char ** argv ) {
    QApplication app ( argc, argv );

    if ( QString ( argv[argc-1] ) == "SvgLogoTest" ) {
        SvgLogoTest svgLogoTest;
        return QTest::qExec ( &svgLogoTest, argc-1, argv );
    } else if ( QString ( argv[argc-1] ) == "LoginWidgetTest" ) {
        LoginWidgetTest loginWidgetTest;
        return QTest::qExec ( &loginWidgetTest, argc-1, argv );
    } else if ( QString ( argv[argc-1] ) == "BarDiagramWidgetTest" ) {
        BarDiagramWidgetTest barDiagramWidgetTest;
        return QTest::qExec ( &barDiagramWidgetTest, argc-1, argv );
    } else if ( QString ( argv[argc-1] ) == "LogoDiagramWidgetTest" ) {
        LogoDiagramWidgetTest logoDiagramWidgetTest;
        return QTest::qExec ( &logoDiagramWidgetTest, argc-1, argv );
    } else if ( QString ( argv[argc-1] ) == "OverlayWidgetTest" ) {
        OverlayWidgetTest overlayWidgetTest;
        return QTest::qExec ( &overlayWidgetTest, argc-1, argv );
    } else {
        qDebug() << "Not a valid test case selected. Add test case name as last parameter. (e.g.: tests -xunitxml SvgLogoTest)";
    }
}
