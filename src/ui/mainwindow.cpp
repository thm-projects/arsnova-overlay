#include "mainwindow.h"

MainWindow::MainWindow ( QWidget * parent, Qt::WindowFlags f ) : QMainWindow ( parent, f ), ui ( new Ui::MainWindow ) {
    ui->setupUi ( this );
    this->menuSignalMapper = new QSignalMapper ( this );
    this->widgetList = new QMap<QString, QWidget *>();

    SplashScreen::instance()->showMessage ( "Running ARSnovawidget developer release" );
    this->addWidget ( "Login", new LoginWidget() );
    this->addWidget ( "Sessions", new SessionWidget() );
    this->addWidget ( "Settings", new QWidget() );
    this->addWidget ( "QR-Code", new QRCodeWidget() );

    this->activateWidget ( "Login" );
}

MainWindow::~MainWindow() {

}

const Ui::MainWindow * const MainWindow::getUi() {
    return this->ui;

}

void MainWindow::addWidget ( QString title, QWidget* widget ) {
    QPushButton * button = new QPushButton ( title );
    button->setCheckable ( true );
    ui->buttonVerticalLayout->addWidget ( button );
    ui->stackedWidget->addWidget ( widget );
    this->widgetList->insert ( title, widget );

    connect ( button, SIGNAL ( clicked ( bool ) ), this->menuSignalMapper, SLOT ( map() ) );
    this->menuSignalMapper->setMapping ( button, button->text() );
    connect ( this->menuSignalMapper, SIGNAL ( mapped ( QString ) ), this, SLOT ( activateWidget ( QString ) ) );
}

void MainWindow::checkLeftMenuButton ( QString title ) {
    QList<QPushButton *> buttons = ui->leftMenu->findChildren<QPushButton *>();
    foreach ( QPushButton * button, buttons ) {
        if ( button->text() == title ) {
            button->setChecked ( true );
        } else {
            button->setChecked ( false );
        }
    }
}

void MainWindow::activateWidget ( QString widgetTitle ) {
    this->checkLeftMenuButton ( widgetTitle );

    QMap<QString, QWidget *>::iterator i = this->widgetList->find ( widgetTitle );

    for ( i = this->widgetList->begin(); i != this->widgetList->end(); i++ ) {
        if ( i.key() == widgetTitle ) ui->stackedWidget->setCurrentWidget ( i.value() );
    }
}

