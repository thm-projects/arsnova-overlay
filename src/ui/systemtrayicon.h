#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <QtGui>

class SystemTrayIcon : public QSystemTrayIcon {

public:
    static SystemTrayIcon * instance();
    
private:
    explicit SystemTrayIcon ( QIcon icon );
    static SystemTrayIcon * _instance;
};

#endif // SYSTEMTRAYICON_H
