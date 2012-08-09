#include "mainwindowtest.h"

MainWindowTest::MainWindowTest ( QObject* parent ) : QObject ( parent ) {}

void MainWindowTest::initTestCase() {
    this->mainWindow = new MainWindow();
}

void MainWindowTest::cleanupTestCase() {}

void MainWindowTest::testShouldDisplayMainWindow() {
    this->mainWindow->show();
    QVERIFY ( this->mainWindow->isVisible() );
}

void MainWindowTest::testThatMainWindowContainsBasicLeftMenu() {
    QList<QPushButton *> buttons = this->mainWindow->getUi()->leftMenu->findChildren<QPushButton *>();
    QVERIFY ( buttons.size() == 4 );
}

