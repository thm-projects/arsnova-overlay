#include "mainwindowtest.h"

MainWindowTest::MainWindowTest ( QObject* parent ) : QObject ( parent ) {}

void MainWindowTest::initTestCase() {
    this->mainWindow = new MainWindow();
    this->mainWindow->show();
}

void MainWindowTest::cleanupTestCase() {
    this->mainWindow->close();
    delete this->mainWindow;
}

void MainWindowTest::testShouldDisplayMainWindow() {
    QVERIFY ( this->mainWindow->isVisible() );
}

void MainWindowTest::testThatMainWindowContainsBasicLeftMenu() {
    QList<QPushButton *> buttons = this->mainWindow->getUi()->leftMenu->findChildren<QPushButton *>();
    QVERIFY ( buttons.size() == 3 );
}

void MainWindowTest::testShouldDisplaySplashScreen() {
    QVERIFY ( ! SplashScreen::instance()->isVisible() );
}

void MainWindowTest::testShouldDisplaySessionWidget() {
    QList<QPushButton *> buttons = this->mainWindow->getUi()->leftMenu->findChildren<QPushButton *>();
    foreach ( QPushButton * button, buttons ) {
        if ( button->text() == "Sessions" ) {
            QTest::mouseClick ( button, Qt::LeftButton );
        }
    }

    QCOMPARE (
        this->mainWindow->getUi()->stackedWidget->currentWidget()->metaObject()->className(),
        "SessionWidget"
    );
}

void MainWindowTest::testShouldDisplayLoginWidget() {
    QList<QPushButton *> buttons = this->mainWindow->getUi()->leftMenu->findChildren<QPushButton *>();
    foreach ( QPushButton * button, buttons ) {
        if ( button->text() == "Login" ) {
            QTest::mouseClick ( button, Qt::LeftButton );
        }
    }

    QCOMPARE (
        this->mainWindow->getUi()->stackedWidget->currentWidget()->metaObject()->className(),
        "LoginWidget"
    );
}
