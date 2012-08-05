#include "mainwindow.h"

MainWindow::MainWindow ( QWidget * parent, Qt::WindowFlags f ) : QMainWindow ( parent, f ), ui ( new Ui::MainWindow ) {
    ui->setupUi ( this );
    this->menuSignalMapper = new QSignalMapper ( this );
    this->widgetList = new QList< QPair<QString, QWidget *> >();

    SplashScreen::instance()->showMessage ( "Running ARSnovawidget developer release" );
    this->addWidget ( "Login", new LoginWidget() );
    this->addWidget ( "Sessions", new QWidget() );
    this->addWidget ( "Settings", new QWidget() );
    
    this->activateWidget("Login");
    
    qDebug() << this->widgetList->count();
    qDebug() << ui->stackedWidget->currentIndex();
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
    qDebug() << ">" << ui->stackedWidget->addWidget ( widget );

    QPair<QString, QWidget *> pair;
    pair.first = title;
    pair.second = widget;

    this->widgetList->append ( pair );

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

    QList< QPair<QString, QWidget *> >::iterator i;
    for ( i = this->widgetList->begin(); i != this->widgetList->end(); ++i ) {
        if ( i->first == widgetTitle ) {
            ui->stackedWidget->setCurrentWidget ( i->second );
        }
    }
}
