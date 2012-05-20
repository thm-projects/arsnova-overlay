#ifndef LOGINWIDGETTEST_H
#define LOGINWIDGETTEST_H

#include <QtTestGui>
#include <QtTest>

#include "qplugin/loginwidget.h"

class LoginWidgetTest : public QObject {

    Q_OBJECT

public:
    explicit LoginWidgetTest ( QObject * parent = 0 );

private:
    LoginWidget * loginWidget;

private slots:
    void initTestCase();
    void cleanupTestCase();
    
    void testShouldShowLoginWidget();
    void testShouldEmitSignalEditingFinished();
    void testShouldEmitSignalExitButtonClicked();
    void testShouldEmitSignalLoginButtonClicked();
};

#endif // LOGINWIDGETTEST_H
