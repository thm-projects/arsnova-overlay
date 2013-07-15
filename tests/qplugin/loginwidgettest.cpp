#include "loginwidgettest.h"

LoginWidgetTest::LoginWidgetTest ( QObject* parent ) : QObject ( parent ) {}

void LoginWidgetTest::initTestCase() {
    this->loginWidget = nullptr;
}

void LoginWidgetTest::cleanupTestCase() {
    delete this->loginWidget;
}

void LoginWidgetTest::testShouldShowLoginWidget() {
    delete this->loginWidget;
    this->loginWidget = new LoginWidget();
    this->loginWidget->show();

    QVERIFY ( this->loginWidget->isVisible() );
}

void LoginWidgetTest::testShouldEmitSignalExitButtonClicked() {
    delete this->loginWidget;
    this->loginWidget = new LoginWidget();
    this->loginWidget->show();

    QSignalSpy spy ( this->loginWidget, SIGNAL ( exitButtonClicked ( ) ) );
    
    this->mouseClick( this->loginWidget->getUi(), Qt::LeftButton, QPoint(345, 205) );

    QCOMPARE ( spy.count(), 1 );
}

void LoginWidgetTest::testShouldEmitSignalLoginButtonClicked() {
    delete this->loginWidget;
    this->loginWidget = new LoginWidget();
    this->loginWidget->show();
  
    this->loginWidget->setText("12345678");
    
    QSignalSpy spy ( this->loginWidget, SIGNAL ( loginButtonClicked ( ) ) );
    
    this->mouseClick( this->loginWidget->getUi(), Qt::LeftButton,  QPoint(145, 205) );

    QCOMPARE ( spy.count(), 1 );
}

void LoginWidgetTest::testShouldNotEmitSignalLoginButtonClickedWithoutSessionKey() {
    delete this->loginWidget;
    this->loginWidget = new LoginWidget();
    this->loginWidget->show();
  
    QSignalSpy spy ( this->loginWidget, SIGNAL ( loginButtonClicked ( ) ) );
    
    this->mouseClick( this->loginWidget->getUi(), Qt::LeftButton,  QPoint(145, 205) );

    QCOMPARE ( spy.count(), 0 );
}

void LoginWidgetTest::testShouldGetAndSetLineEditText() {
    this->loginWidget->setText ( "test321" );

    QCOMPARE ( this->loginWidget->text(), QString ( "test321" ) );
}

void LoginWidgetTest::testShouldClearLineEditText() {
    this->loginWidget->clear();

    QVERIFY ( this->loginWidget->text().isEmpty() );
}
