#include "mainwindow.h"

MainWindow::MainWindow ( QWidget * parent, Qt::WindowFlags f ) : QMainWindow ( parent, f ), ui ( new Ui::MainWindow ) {
    ui->setupUi ( this );
    SplashScreen::instance()->showMessage("Running ARSnovawidget developer release");
}

MainWindow::~MainWindow() {

}

const Ui::MainWindow * const MainWindow::getUi() {
    return this->ui;
}
