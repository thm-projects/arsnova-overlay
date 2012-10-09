/***************************************************************************
 *   Copyright (C) 2012  Paul-Christian Volkmer
 *   <paul-christian.volkmer@mni.thm.de>
 *
 *   This file is part of ARSnovaDesktop.
 *
 *   ARSnovaDesktop is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   ARSnovaDesktop is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with ARSnovaDesktop.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include <QtCore>
#include <QtGui>

#include "ui/overlaywidget.h"
#include "ui/mainwindow.h"
#include "svglogo.h"
#include "understandingresponse.h"
#include "httpconnection.h"
#include "ui/splashscreen.h"
#include "ui/systemtrayicon.h"

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

    SplashScreen::instance()->showMessage ( "Starting ARSnovaDesktop" );
    SplashScreen::instance()->show();

    MainWindow mainWindow;
    mainWindow.show();

    SystemTrayIcon::instance()->show();

#ifdef __APPLE__
    stopApplication();
#endif
    return app.exec();
}
