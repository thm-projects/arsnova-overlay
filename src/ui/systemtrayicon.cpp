#include "systemtrayicon.h"

std::atomic<SystemTrayIcon *> SystemTrayIcon::_instance ( nullptr );

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
    static std::mutex mutex;
    SystemTrayIcon * systemTrayIcon = _instance.load();
    if ( _instance == nullptr ) {
        std::lock_guard<std::mutex>  lock ( mutex );
        if ( _instance == nullptr ) {
            systemTrayIcon = new SystemTrayIcon ( QIcon ( ":images/arsnova.svg" ) );
            _instance.store ( systemTrayIcon );
        }
    }
    return systemTrayIcon;
}

void SystemTrayIcon::destroy() {
    delete _instance.load();
}

void SystemTrayIcon::addExitAction() {
    QAction * exitAction = new QAction ( QIcon ( ":images/images/application-exit.png" ), tr ( "Exit" ), this );
    menu->addAction ( exitAction );
    connect ( exitAction, SIGNAL ( triggered ( bool ) ), this, SLOT ( exitApplication () ) );
}

void SystemTrayIcon::exitApplication() {
    exit ( 0 );
}


