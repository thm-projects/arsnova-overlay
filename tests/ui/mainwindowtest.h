#ifndef MAINWINDOWTEST_H
#define MAINWINDOWTEST_H

#include <QtTest>
#include <QtTestGui>
#include "ui/mainwindow.h"

class MainWindowTest : public QObject {

    Q_OBJECT

public:
    explicit MainWindowTest ( QObject* parent = 0 );

private:
    MainWindow * mainWindow;

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testShouldDisplayMainWindow();
    void testThatMainWindowContainsBasicLeftMenu();
    void testShouldDisplaySplashScreen();

};

#endif // MAINWINDOWTEST_H
