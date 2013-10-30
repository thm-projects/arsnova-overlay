#include <QtCore>
#include <QtGui>
#include <QApplication>

#include "svglogotest.h"
#include "ui/loginwidgettest.h"
#include "ui/bardiagramwidgettest.h"
#include "ui/logodiagramwidgettest.h"
#include "ui/emotediagramwidgettest.h"
#include "ui/sessioninformationwidgettest.h"
#include "ui/overlaywidgettest.h"
#include "ui/qrcodewidgettest.h"
#include "ui/mainwindowtest.h"
#include "sessioncontexttest.h"
#include "ui/systemtrayicontest.h"
#include "ui/sessionwidgettest.h"
#include "feedbackresponsetest.h"

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
    } else if ( QString ( argv[argc-1] ) == "EmoteDiagramWidgetTest" ) {
        EmoteDiagramWidgetTest emoteDiagramWidgetTest;
        return QTest::qExec ( &emoteDiagramWidgetTest, argc-1, argv );
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
    } else if ( QString ( argv[argc-1] ) == "SystemTrayIconTest" ) {
        SystemTrayIconTest systemTrayIconTest;
        return QTest::qExec ( &systemTrayIconTest, argc-1, argv );
    } else if ( QString ( argv[argc-1] ) == "SessionWidgetTest" ) {
        SessionWidgetTest sessionWidgetTest;
        return QTest::qExec ( &sessionWidgetTest, argc-1, argv );
    } else if ( QString ( argv[argc-1] ) == "FeedbackResponseTest" ) {
        FeedbackResponseTest feedbackResponseTest;
        return QTest::qExec ( &feedbackResponseTest, argc-1, argv );
    } else {
        qDebug() << "Not a valid test case selected. Add test case name as last parameter. (e.g.: tests -xunitxml SvgLogoTest)";
    }
}
