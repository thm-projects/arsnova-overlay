#include "mainwindow.h"

MainWindow::MainWindow ( QWidget *parent, Qt::WindowFlags f ) : QMainWindow ( parent, f ), ui ( new Ui::MainWindow ) {
    ui->setupUi ( this );

    QRect frect = frameGeometry();
    frect.moveCenter ( QDesktopWidget().availableGeometry().center() );
    move ( frect.topLeft() );

    infoDialog = new InfoDialog ( this );

    this->menuSignalMapper = new QSignalMapper ( this );
    this->widgetList = new QMap<QString, QWidget *>();
    this->sessionContext = new SessionContext ( new HttpConnection() );

    QRCodeWidget *qrwidget = new QRCodeWidget ( this->sessionContext, this->ui->stackedWidget );

    this->addWidget ( "Login", new LoginWidget() );
    this->addWidget ( "Sessions", new SessionWidget ( this->sessionContext ) );
    this->addWidget ( "QR-Code", qrwidget );
    this->addWidget ( "Settings", new SettingsWidget ( this->sessionContext ) );

    this->activateWidget ( "Login" );
    this->connectLoginWidget();
    
    this->overlayWidget = new OverlayWidget ( this->sessionContext, QApplication::desktop()->screen() );
    this->overlayWidget->setVisible ( false );

    connect ( SystemTrayIcon::instance(), SIGNAL ( activated ( QSystemTrayIcon::ActivationReason ) ), this, SLOT ( onSystemTrayActivated ( QSystemTrayIcon::ActivationReason ) ) );
    connect ( this->sessionContext, SIGNAL ( error ( SessionContext::Error ) ) , this, SLOT ( onContextError ( SessionContext::Error ) ) );

    connect ( this->ui->actionAbout, &QAction::triggered, [ = ] ( bool ) {
        if ( ! infoDialog->isVisible() ) {
            infoDialog->show();
        }
    } );

    connect ( this->ui->actionExit, &QAction::triggered, [ = ] ( bool ) {
        exit ( 0 );
    } );

    connect ( this->ui->actionLogin, &QAction::triggered, [ = ] ( bool ) {
        this->activateWidget ( "Login" );
    } );
}

MainWindow::~MainWindow() {
    this->disconnectAll();
    SystemTrayIcon::destroy();
    this->overlayWidget->close();
    delete overlayWidget;
    delete widgetList;
    int widgetCount =  ui->stackedWidget->count();
    for ( int i = 0; i < widgetCount ; i++ ) {
        ui->stackedWidget->widget ( 0 )->close();
        delete ui->stackedWidget->widget ( 0 );
    }
    delete ui;
    delete sessionContext;
}

void MainWindow::disconnectAll() {
    disconnect ( SystemTrayIcon::instance(), SIGNAL ( activated ( QSystemTrayIcon::ActivationReason ) ), this, SLOT ( onSystemTrayActivated ( QSystemTrayIcon::ActivationReason ) ) );
    disconnect ( this->menuSignalMapper, SIGNAL ( mapped ( QString ) ), this, SLOT ( activateWidget ( QString ) ) );
    disconnect ( this->findWidget ( "Login" ), SIGNAL ( exitButtonClicked() ), this, SLOT ( exitApplication() ) );
    disconnect ( this->findWidget ( "Login" ), SIGNAL ( loginButtonClicked() ), this, SLOT ( sessionLogin() ) );
}

const Ui::MainWindow *const MainWindow::getUi() {
    return this->ui;
}

void MainWindow::closeEvent ( QCloseEvent *event ) {
    if ( QMessageBox::StandardButton::Yes ==
            QMessageBox::question (
                this,
                tr ( "Application will be hidden" ),
                tr ( "ARSnova Overlay will be hidden. Do you wish to close this application instead?" ),
                QMessageBox::Yes|QMessageBox::No,
                QMessageBox::No
            ) ) {
        exit ( 0 );
    }
    QMainWindow::closeEvent ( event );
}

void MainWindow::addWidget ( QString title, QWidget *widget ) {
    QPushButton *button = new QPushButton ( title );
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

void MainWindow::onContextError ( SessionContext::Error e ) {
    this->activateWidget ( "Login" );
    this->getUi()->statusbar->showMessage ( tr ( "Unable to request session from server" ), 5000 );
}

void MainWindow::activateWidget ( QString widgetTitle ) {
    this->checkLeftMenuButton ( widgetTitle );

    QWidget *widget = this->findWidget ( widgetTitle );
    if ( widget != nullptr ) {
        ui->stackedWidget->setCurrentWidget ( widget );
        widget->setFocus();
    }
}

QWidget *MainWindow::findWidget ( QString widgetTitle ) {
    QMap<QString, QWidget *>::iterator i = this->widgetList->find ( widgetTitle );

    for ( i = this->widgetList->begin(); i != this->widgetList->end(); ++i ) {
        if ( i.key() == widgetTitle ) return i.value();
    }

    return nullptr;
}

void MainWindow::connectLoginWidget() {
    LoginWidget *loginWidget = ( LoginWidget * ) this->findWidget ( "Login" );
    if ( loginWidget != nullptr ) {
        connect ( loginWidget, &LoginWidget::exitButtonClicked, [ = ]() {
            exit ( 0 );
        } );
        connect ( loginWidget, SIGNAL ( loginButtonClicked() ), this, SLOT ( sessionLogin() ) );
    }
}

void MainWindow::sessionLogin() {
    this->getUi()->statusbar->showMessage ( tr ( "Connected to session" ), 5000 );
    LoginWidget *loginWidget = ( LoginWidget * ) this->findWidget ( "Login" );
    if ( loginWidget != nullptr ) {
        this->sessionContext->connection()->requestSession ( loginWidget->text() );
        this->activateWidget ( "Sessions" );
    }
}
