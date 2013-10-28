#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

#include "version.h"
#include "ui_mainwindow.h"
#include "ui/loginwidget.h"
#include "ui/qrcodewidget.h"
#include "ui/sessionwidget.h"
#include "ui/overlaywidget.h"
#include "sessioncontext.h"
#include "ui/systemtrayicon.h"
#include "httpconnection.h"
#include "ui/settingswidget.h"
#include "ui/infodialog.h"

class MainWindow : public QMainWindow, Ui::MainWindow {
    Q_OBJECT

public:
    explicit MainWindow ( QWidget * parent = 0, Qt::WindowFlags f = 0 );
    virtual ~MainWindow();
    const Ui::MainWindow * const getUi();
    void addWidget ( QString title, QWidget * widget );

private:
    Ui::MainWindow * ui;
    QSignalMapper * menuSignalMapper;
    QMap<QString, QWidget *> * widgetList;
    OverlayWidget * overlayWidget;
    SessionContext * sessionContext;
    InfoDialog * infoDialog;

    void checkLeftMenuButton ( QString title );
    QWidget * findWidget ( QString widgetTitle );
    void connectLoginWidget();

    void disconnectAll();

private slots:
    void onSystemTrayActivated ( QSystemTrayIcon::ActivationReason reason );
    void activateWidget ( QString widgetTitle );
    void sessionLogin();
    void onContextError(SessionContext::Error e);
    void exitApplication();
    void showInfoDialog();
    void showLoginWidget();
};

#endif // MAINWINDOW_H
