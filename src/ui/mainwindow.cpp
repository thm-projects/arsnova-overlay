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
    ui->buttonHorizontalLayout->addSpacing ( 1 );
    this->addWidget ( "Sessions", new SessionWidget ( this->sessionContext ) );
    this->addWidget ( "QR-Code", qrwidget );
    this->addWidget ( "Settings", new SettingsWidget ( this->sessionContext ) );
    ui->buttonHorizontalLayout->addStretch();
    infoButton = new QPushButton ( "About" );
    infoButton->setAccessibleName ( "infoButton" );
    ui->buttonHorizontalLayout->addWidget ( infoButton );
    this->activateWidget ( "Sessions" );

    this->overlayWidget = new OverlayWidget ( this->sessionContext, QApplication::desktop()->screen() );
    this->overlayWidget->setVisible ( false );

    connect ( this->sessionContext, &SessionContext::error, [=] ( SessionContext::Error error ) {
        this->activateWidget ( "Sessions" );
        this->getUi()->statusbar->showMessage ( tr ( "Unable to request session from server" ), 5000 );
    } );

    connect ( SystemTrayIcon::instance(), &SystemTrayIcon::activated, [=] ( QSystemTrayIcon::ActivationReason reason ) {
        if ( reason == QSystemTrayIcon::Trigger ) {
            this->setVisible ( ! this->isVisible() );
        }
    } );

    connect ( this->infoButton, &QPushButton::clicked, [=] ( ) {
        if ( ! infoDialog->isVisible() ) {
            infoDialog->show();
        }
    } );
}

MainWindow::~MainWindow() {
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
    ui->buttonHorizontalLayout->addWidget ( button );
    ui->stackedWidget->addWidget ( widget );
    this->widgetList->insert ( title, widget );

    connect ( button, SIGNAL ( clicked ( bool ) ), this->menuSignalMapper, SLOT ( map() ) );
    this->menuSignalMapper->setMapping ( button, button->text() );
    connect ( this->menuSignalMapper, SIGNAL ( mapped ( QString ) ), this, SLOT ( activateWidget ( QString ) ) );
}

void MainWindow::checkTopMenuButton ( QString title ) {
    QList<QPushButton *> buttons = ui->topMenu->findChildren<QPushButton *>();
    for ( QPushButton * button : buttons ) {
        button->setChecked ( button->text() == title );
    }
}

void MainWindow::activateWidget ( QString widgetTitle ) {
    this->checkTopMenuButton ( widgetTitle );

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
