#ifndef LOGINWIDGETTEST_H
#define LOGINWIDGETTEST_H

#include <QtTest>
#include <QtTest/QtTestGui>
#include <QtDeclarative>

#include "qplugin/loginwidget.h"

class LoginWidgetTest : public QObject {

    Q_OBJECT

public:
    explicit LoginWidgetTest ( QObject * parent = 0 );

private:
    LoginWidget * loginWidget;

    void mouseClick ( QGraphicsScene * scene, Qt::MouseButton button, QPoint position ) {
        QGraphicsSceneMouseEvent pressEvent ( QEvent::GraphicsSceneMousePress );
        pressEvent.setScenePos ( position );
        pressEvent.setButton ( button );
        QApplication::sendEvent ( scene, &pressEvent );

        QGraphicsSceneMouseEvent releaseEvent ( QEvent::GraphicsSceneMouseRelease );
        releaseEvent.setScenePos ( position );
        releaseEvent.setButton ( button );
        QApplication::sendEvent ( scene, &releaseEvent );
    }

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testShouldShowLoginWidget();
    void testShouldEmitSignalExitButtonClicked();
    void testShouldEmitSignalLoginButtonClicked();
    void testShouldNotEmitSignalLoginButtonClickedWithoutSessionKey();
    void testShouldGetAndSetLineEditText();
    void testShouldClearLineEditText();
    void testShouldEmitSignalOnEnterKey();
    void testShouldEmitSignalOnReturnKey();
};

#endif // LOGINWIDGETTEST_H
