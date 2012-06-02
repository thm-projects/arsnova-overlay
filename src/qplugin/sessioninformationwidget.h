#ifndef SESSIONINFORMATIONWIDGET_H
#define SESSIONINFORMATIONWIDGET_H

#include <QtGui>
#include "ui_sessioninformationwidget.h"

class SessionInformationWidget : public QWidget, Ui::SessionInformationWidget {
    Q_OBJECT

public:
    explicit SessionInformationWidget ( QWidget* parent = 0, Qt::WindowFlags f = 0 );

    void updateSessionLabel ( QString sessionName, QString sessionID );
    void updateCounterLabel ( int feedback, int onlineUsers );
    void updateProgressBar ( int value, int max );

    const Ui::SessionInformationWidget * const getUi();

private:
    Ui::SessionInformationWidget * _ui;
};

#endif // SESSIONINFORMATIONWIDGET_H
