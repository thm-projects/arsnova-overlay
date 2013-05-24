#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <QtGui>
#include <atomic>
#include <mutex>

class SystemTrayIcon : public QSystemTrayIcon {

    Q_OBJECT

public:
    static SystemTrayIcon * instance();
    static void destroy();
    virtual ~SystemTrayIcon();

private:
    explicit SystemTrayIcon ( QIcon icon );
    void addExitAction();

    static std::atomic<SystemTrayIcon *> _instance;
    QMenu * menu;

private slots:
    void exitApplication ();
};

#endif // SYSTEMTRAYICON_H


