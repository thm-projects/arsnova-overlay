#include <QtCore>
#include <QtGui>
#include <QApplication>

#include "svglogotest.h"
#include "qplugin/loginwidgettest.h"
#include "qplugin/bardiagramwidgettest.h"
#include "qplugin/logodiagramwidgettest.h"
#include "qplugin/sessioninformationwidgettest.h"
#include "ui/overlaywidgettest.h"
#include "ui/qrcodewidgettest.h"
#include "ui/mainwindowtest.h"
#include "sessioncontexttest.h"
#include "ui/splashscreentest.h"

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
    } else if ( QString ( argv[argc-1] ) == "SessionInformationWidgetTest" ) {
        SessionInformationWidgetTest sessionInformationWidgetTest;
        return QTest::qExec ( &sessionInformationWidgetTest, argc-1, argv );
    } else if ( QString ( argv[argc-1] ) == "QRCodeWidgetTest" ) {
        QRCodeWidgetTest qrCodeWidgetTest;
        return QTest::qExec ( &qrCodeWidgetTest, argc-1, argv );
    } else if ( QString ( argv[argc-1] ) == "MainWindowTest" ) {
        MainWindowTest mainWindowTest;
        return QTest::qExec ( &mainWindowTest, argc-1, argv );
    } else if ( QString ( argv[argc-1] ) == "SessionContextTest" ) {
        SessionContextTest sessionContextTest;
        return QTest::qExec ( &sessionContextTest, argc-1, argv );
    } else if ( QString ( argv[argc-1] ) == "SplashScreenTest" ) {
        SplashScreenTest splashScreenTest;
        return QTest::qExec ( &splashScreenTest, argc-1, argv );
    } else {
        qDebug() << "Not a valid test case selected. Add test case name as last parameter. (e.g.: tests -xunitxml SvgLogoTest)";
    }
}
