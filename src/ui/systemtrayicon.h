#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <QtGui>

class SystemTrayIcon : public QSystemTrayIcon {

    Q_OBJECT

public:
    static SystemTrayIcon * instance();

private:
    explicit SystemTrayIcon ( QIcon icon );
    void addExitAction();

    static SystemTrayIcon * _instance;
    QMenu * menu;

private slots:
    void exitApplication ();
};

#endif // SYSTEMTRAYICON_H
