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

void MainWindowTest::testThatMainWindowContainsBasicTopMenu() {
    QList<QPushButton *> buttons = this->mainWindow->getUi()->topMenu->findChildren<QPushButton *>();
    // 3 Widgets and About Button
    QVERIFY ( buttons.size() == 4 );
}

void MainWindowTest::testShouldDisplaySessionWidget() {
    QList<QPushButton *> buttons = this->mainWindow->getUi()->topMenu->findChildren<QPushButton *>();
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
    QList<QPushButton *> buttons = this->mainWindow->getUi()->topMenu->findChildren<QPushButton *>();
    foreach ( QPushButton * button, buttons ) {
        if ( button->text() == "Login" ) {
            QTest::mouseClick ( button, Qt::LeftButton );
        }
    }

    QCOMPARE (
        this->mainWindow->getUi()->stackedWidget->currentWidget()->metaObject()->className(),
        "SessionWidget"
    );
}
