/***************************************************************************
 *   Copyright (C) 2014  Paul-Christian Volkmer
 *   <paul-christian.volkmer@mni.thm.de>
 *
 *   This file is part of ARSnova Overlay.
 *
 *   ARSnova Overlay is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   ARSnova Overlay is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with ARSnova Overlay.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "systemtrayicon.h"
#include "mainwindow.h"

SystemTrayIcon * SystemTrayIcon::_instance = nullptr;

SystemTrayIcon::SystemTrayIcon ( QIcon icon ) : QSystemTrayIcon ( icon, QApplication::desktop() ) {
    menu = new QMenu ( "ARSnova Overlay" );
    this->addExitAction();
    this->setContextMenu ( menu );
}

SystemTrayIcon::~SystemTrayIcon() {
    foreach ( QAction * action, this->menu->actions() ) {
        this->menu->removeAction ( action );
        delete action;
    }
    delete this->menu;
}

SystemTrayIcon * SystemTrayIcon::instance() {
    if ( _instance == nullptr ) {
#ifdef __WIN32__
        _instance = new SystemTrayIcon ( QIcon ( ":images/images/logo_64.png" ) );
#else
        _instance = new SystemTrayIcon ( QIcon ( ":images/arsnova.svg" ) );
#endif
    }
    return _instance;
}

void SystemTrayIcon::destroy() {
    delete _instance;
}

void SystemTrayIcon::addExitAction() {
    QAction * exitAction = new QAction ( QIcon ( ":images/images/application-exit.png" ), tr ( "Exit" ), this );
    menu->addAction ( exitAction );
    connect ( exitAction, SIGNAL ( triggered ( bool ) ), this, SLOT ( exitApplication () ) );
}

void SystemTrayIcon::exitApplication() {
    exit ( 0 );
}
