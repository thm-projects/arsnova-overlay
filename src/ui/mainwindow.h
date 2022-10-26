#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <memory>

#include "version.h"
#include "ui_mainwindow.h"
#include "ui/qrcodewidget.h"
#include "ui/sessionwidget.h"
#include "ui/overlaywidget.h"
#include "ui/settingswidget.h"
#include "ui/infodialog.h"
#include "ui/systemtrayicon.h"
#include "sessioncontext.h"
#include "httpconnection.h"


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow ( QWidget *parent = 0, Qt::WindowFlags f = 0 );
    virtual ~MainWindow();
    const Ui::MainWindow *const getUi();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<InfoDialog> infoDialog;
    QPushButton *infoButton;

    QSignalMapper *menuSignalMapper;
    QMap<QString, QWidget *> *widgetList;
    OverlayWidget *overlayWidget;
    SessionContext *sessionContext;

    void checkTopMenuButton ( QString title );
    QWidget *findWidget ( QString widgetTitle );
    void addWidget ( QString title, QWidget *widget );

protected:
    void closeEvent ( QCloseEvent * event ) override;

private slots:
    void activateWidget ( QString widgetTitle );
};

#endif // MAINWINDOW_H

