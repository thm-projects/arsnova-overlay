#ifndef SESSIONINFORMATIONWIDGET_H
#define SESSIONINFORMATIONWIDGET_H

#include <QtGui>
#include "ui_sessioninformationwidget.h"

class SessionInformationWidget : public QWidget, Ui::SessionInformationWidget {
    Q_OBJECT

public:
    explicit SessionInformationWidget ( QWidget* parent = 0, Qt::WindowFlags f = 0 );
    virtual ~SessionInformationWidget();
    void updateSessionLabel ( QString sessionName, QString sessionID );
    void updateCounterLabel ( int feedback, int onlineUsers );
    void updateProgressBar ( int value, int max );
    /** Returns user interface of this widget.
     * This method is helpfull if someone needs direct access to the
     * user interface itself e.g. testing.
     * @return User interface
     */
    const Ui::SessionInformationWidget * const getUi();

private:
    Ui::SessionInformationWidget * _ui;
};

#endif // SESSIONINFORMATIONWIDGET_H
