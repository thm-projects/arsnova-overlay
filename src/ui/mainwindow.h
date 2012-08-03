#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

#include "ui_mainwindow.h"
#include "ui/splashscreen.h"

class MainWindow : public QMainWindow, Ui::MainWindow {
    Q_OBJECT

public:
    explicit MainWindow ( QWidget * parent = 0, Qt::WindowFlags f = 0 );
    virtual ~MainWindow();
    const Ui::MainWindow * const getUi();

private:
    Ui::MainWindow * ui;

};

#endif // MAINWINDOW_H
