#include "mainwindow.h"

MainWindow::MainWindow ( QWidget * parent, Qt::WindowFlags f ) : QMainWindow ( parent, f ), ui ( new Ui::MainWindow ) {
    ui->setupUi ( this );
    SplashScreen::instance()->showMessage ( "Running ARSnovawidget developer release" );
}

MainWindow::~MainWindow() {

}

const Ui::MainWindow * const MainWindow::getUi() {
    return this->ui;
}

void MainWindow::uncheckLeftMenuButtons() {
    QList<QPushButton *> buttons = ui->leftMenu->findChildren<QPushButton *>();
    foreach ( QPushButton * button, buttons ) {
        button->setChecked ( false );
    }
}

void MainWindow::on_loginButton_clicked () {
    this->uncheckLeftMenuButtons();
    ui->loginButton->setChecked ( true );
    qDebug() << ui->tabWidget;
}

void MainWindow::on_sessionsButton_clicked () {
    this->uncheckLeftMenuButtons();
    ui->sessionsButton->setChecked ( true );
}

void MainWindow::on_settingsButton_clicked () {
    this->uncheckLeftMenuButtons();
    ui->settingsButton->setChecked ( true );
}



