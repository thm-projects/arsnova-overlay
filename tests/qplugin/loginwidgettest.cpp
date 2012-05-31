#include "loginwidgettest.h"

LoginWidgetTest::LoginWidgetTest ( QObject* parent ) : QObject ( parent ) {}

void LoginWidgetTest::initTestCase() {
    this->loginWidget = new LoginWidget();
}

void LoginWidgetTest::cleanupTestCase() {
    delete this->loginWidget;
}

void LoginWidgetTest::testShouldShowLoginWidget() {
    this->loginWidget->show();
    QVERIFY ( this->loginWidget->isVisible() );
}

void LoginWidgetTest::testShouldEmitSignalEditingFinished() {
    QSignalSpy spy ( this->loginWidget, SIGNAL ( editingFinished ( ) ) );
    QTest::keyClick ( this->loginWidget->getUi()->sessionIdEdit,  Qt::Key_0 );
    QTest::keyClick ( this->loginWidget->getUi()->sessionIdEdit,  Qt::Key_1 );
    QTest::keyClick ( this->loginWidget->getUi()->sessionIdEdit,  Qt::Key_2 );
    QTest::keyClick ( this->loginWidget->getUi()->sessionIdEdit,  Qt::Key_3 );
    QTest::keyClick ( this->loginWidget->getUi()->sessionIdEdit,  Qt::Key_4 );
    QTest::keyClick ( this->loginWidget->getUi()->sessionIdEdit,  Qt::Key_5 );
    QTest::keyClick ( this->loginWidget->getUi()->sessionIdEdit,  Qt::Key_6 );
    QTest::keyClick ( this->loginWidget->getUi()->sessionIdEdit,  Qt::Key_7 );
    QTest::keyClick ( this->loginWidget->getUi()->sessionIdEdit,  Qt::Key_Enter );

    QCOMPARE ( spy.count(), 1 );
}

void LoginWidgetTest::testShouldEmitSignalExitButtonClicked() {
    QSignalSpy spy ( this->loginWidget, SIGNAL ( exitButtonClicked ( ) ) );
    QTest::mouseClick ( this->loginWidget->getUi()->exitButton,  Qt::LeftButton );

    QCOMPARE ( spy.count(), 1 );
}

void LoginWidgetTest::testShouldEmitSignalLoginButtonClicked() {
    QSignalSpy spy ( this->loginWidget, SIGNAL ( loginButtonClicked ( ) ) );
    QTest::mouseClick ( this->loginWidget->getUi()->loginButton,  Qt::LeftButton );

    QCOMPARE ( spy.count(), 1 );
}

void LoginWidgetTest::testShouldSetLineEditText() {
    this->loginWidget->setText ( "test321" );

    QCOMPARE ( this->loginWidget->getUi()->sessionIdEdit->text(), QString ( "test321" ) );
}

void LoginWidgetTest::testShouldGetLineEditText() {
    this->loginWidget->getUi()->sessionIdEdit->setText ( "test123" );

    QCOMPARE ( this->loginWidget->text(), QString ( "test123" ) );
}

void LoginWidgetTest::testShouldClearLineEditText() {
    this->loginWidget->clear();

    QVERIFY ( this->loginWidget->getUi()->sessionIdEdit->text().isEmpty() );
}
