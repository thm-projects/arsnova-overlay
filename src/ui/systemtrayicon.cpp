#include "systemtrayicon.h"

SystemTrayIcon * SystemTrayIcon::_instance = nullptr;

SystemTrayIcon::SystemTrayIcon ( QIcon icon ) : QSystemTrayIcon ( icon ) {
}

SystemTrayIcon * SystemTrayIcon::instance() {
    if ( _instance == nullptr ) {
        _instance = new SystemTrayIcon ( QIcon ( ":images/arsnova.svg" ) );
    }
    return _instance;
}
