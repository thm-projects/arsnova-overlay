#include "mainwindow.h"

MainWindow::MainWindow ( QWidget * parent, Qt::WindowFlags f ) : QMainWindow ( parent, f ), ui ( new Ui::MainWindow ) {
    ui->setupUi ( this );

    QRect frect = frameGeometry();
    frect.moveCenter ( QDesktopWidget().availableGeometry().center() );
    move ( frect.topLeft() );

    this->menuSignalMapper = new QSignalMapper ( this );
    this->widgetList = new QMap<QString, QWidget *>();
    this->sessionContext = new SessionContext ( new HttpConnection() );

    SplashScreen::instance()->showMessage (
        QString ( "Running ARSnovawidget" )
        + " " + VERSION_MAJOR
        + "." + VERSION_MINOR
        + "." + VERSION_PATCH
    );

    this->addWidget ( "Login", new LoginWidget() );
    this->connectLoginWidget();

    this->addWidget ( "Sessions", new SessionWidget ( this->sessionContext ) );
    this->addWidget ( "Settings", new QWidget() );

    QRCodeWidget * qrwidget = new QRCodeWidget ( this->sessionContext );
    qrwidget->setUrl ( QUrl ( "https://ars.thm.de/" ) );
    this->addWidget ( "QR-Code", qrwidget );
    
    this->activateWidget ( "Login" );

    this->overlayWidget = new OverlayWidget ( this->sessionContext, this );
    this->overlayWidget->setVisible ( false );

    connect ( SystemTrayIcon::instance(), SIGNAL ( activated ( QSystemTrayIcon::ActivationReason ) ), this, SLOT ( onSystemTrayActivated ( QSystemTrayIcon::ActivationReason ) ) );
}

MainWindow::~MainWindow() {
    this->overlayWidget->close();
    delete this->overlayWidget;
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

void MainWindow::onSystemTrayActivated ( QSystemTrayIcon::ActivationReason reason ) {
    if ( reason == QSystemTrayIcon::Trigger ) {
        this->setVisible ( ! this->isVisible() );
    }
}

void MainWindow::activateWidget ( QString widgetTitle ) {
    this->checkLeftMenuButton ( widgetTitle );

    QWidget * widget = this->findWidget ( widgetTitle );
    if ( widget != nullptr ) ui->stackedWidget->setCurrentWidget ( widget );
}

QWidget * MainWindow::findWidget ( QString widgetTitle ) {
    QMap<QString, QWidget *>::iterator i = this->widgetList->find ( widgetTitle );

    for ( i = this->widgetList->begin(); i != this->widgetList->end(); i++ ) {
        if ( i.key() == widgetTitle ) return i.value();
    }

    return nullptr;
}

void MainWindow::connectLoginWidget() {
    LoginWidget * loginWidget = ( LoginWidget * ) this->findWidget ( "Login" );
    if ( loginWidget != nullptr ) {
        connect ( loginWidget, SIGNAL ( returnPressed() ), this, SLOT ( sessionLogin() ) );
        connect ( loginWidget, SIGNAL ( exitButtonClicked() ), this, SLOT ( close() ) );
        connect ( loginWidget, SIGNAL ( loginButtonClicked() ), this, SLOT ( sessionLogin() ) );
    }
}

void MainWindow::sessionLogin() {
    LoginWidget * loginWidget = ( LoginWidget * ) this->findWidget ( "Login" );
    if ( loginWidget != nullptr ) {
        this->sessionContext->connection()->requestSession ( loginWidget->text() );
        this->activateWidget ( "Sessions" );
    }
}
