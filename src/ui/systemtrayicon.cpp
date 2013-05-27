#include "systemtrayicon.h"

SystemTrayIcon * SystemTrayIcon::_instance = nullptr;

SystemTrayIcon::SystemTrayIcon ( QIcon icon ) : QSystemTrayIcon ( icon ) {
    menu = new QMenu ( "ARSnovaDesktop" );
    this->addExitAction();
    this->setContextMenu ( menu );
}

SystemTrayIcon::~SystemTrayIcon() {
    disconnect ( SIGNAL ( triggered ( bool ) ), this, SLOT ( exitApplication () ) );
    foreach ( QAction * action, this->menu->actions() ) {
        this->menu->removeAction ( action );
        delete action;
    }
    delete this->menu;
}

SystemTrayIcon * SystemTrayIcon::instance() {
    if ( _instance == nullptr ) {
        _instance = new SystemTrayIcon ( QIcon ( ":images/arsnova.svg" ) );
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


