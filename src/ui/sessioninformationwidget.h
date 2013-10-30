#ifndef SESSIONINFORMATIONWIDGET_H
#define SESSIONINFORMATIONWIDGET_H

#include <QtGui>
#include <QtDeclarative>

#include "audiencequestioncountresponse.h"

class SessionInformationWidget : public QDeclarativeView {
    Q_OBJECT

public:
    explicit SessionInformationWidget ( QWidget * parent = 0, Qt::WindowFlags f = 0 );
    virtual ~SessionInformationWidget();
    void updateSessionLabel ( QString sessionName, QString sessionID );
    void updateCounterLabel ( int feedback, int onlineUsers );
    void updateProgressBar ( int value, int max );
    void updateAudienceQuestionCount ( AudienceQuestionCountResponse response );
    /** Returns user interface of this widget.
     * This method is helpfull if someone needs direct access to the
     * user interface itself e.g. testing.
     * @return User interface
     */
    QGraphicsScene * const getUi();

private:
    QDeclarativeItem * item;

private slots:
    void onCloseButtonClicked();

signals:
    void closeButtonClicked();
};

#endif // SESSIONINFORMATIONWIDGET_H
