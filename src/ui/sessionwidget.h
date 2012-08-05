#ifndef SESSIONWIDGET_H
#define SESSIONWIDGET_H

#include <QtGui>
#include "ui_sessionwidget.h"

class SessionWidget : public QWidget, Ui::SessionWidget {
    Q_OBJECT

public:
    explicit SessionWidget ( QWidget* parent = 0, Qt::WindowFlags f = 0 );
    const Ui::SessionWidget * const getUi();

private:
    Ui::SessionWidget * _ui;
};

#endif // SESSIONWIDGET_H
