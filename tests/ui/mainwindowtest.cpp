#include "mainwindowtest.h"

MainWindowTest::MainWindowTest ( QObject* parent ) : QObject ( parent ) {}

void MainWindowTest::initTestCase() {
    this->mainWindow = new MainWindow();
    this->mainWindow->show();
}

void MainWindowTest::cleanupTestCase() {
    delete this->mainWindow;
}

void MainWindowTest::testShouldDisplayMainWindow() {
    QVERIFY ( this->mainWindow->isVisible() );
}

void MainWindowTest::testThatMainWindowContainsBasicLeftMenu() {
    QList<QPushButton *> buttons = this->mainWindow->getUi()->leftMenu->findChildren<QPushButton *>();
    QVERIFY ( buttons.size() == 4 );
}

void MainWindowTest::testShouldDisplaySplashScreen() {
    QVERIFY ( SplashScreen::instance()->isVisible() );
}

