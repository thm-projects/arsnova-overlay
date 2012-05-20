#ifndef BARDIAGRAMWIDGET_H
#define BARDIAGRAMWIDGET_H

#include <QtGui>
#include "ui_bardiagramwidget.h"

class BarDiagramWidget : public QWidget, Ui::BarDiagramWidget {
    Q_OBJECT

public:
    explicit BarDiagramWidget ( QWidget* parent = 0, Qt::WindowFlags f = 0 );

private:
    Ui::BarDiagramWidget * ui;
};

#endif // BARDIAGRAMWIDGET_H
