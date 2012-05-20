#ifndef BARDIAGRAMWIDGET_H
#define BARDIAGRAMWIDGET_H

#include <QtGui>
#include "ui_bardiagramwidget.h"

class BarDiagramWidget : public QWidget, Ui::BarDiagramWidget {
    Q_OBJECT

public:
    explicit BarDiagramWidget ( QWidget* parent = 0, Qt::WindowFlags f = 0 );
    const Ui::BarDiagramWidget * const getUi();
    void updateGraphicsBar ( int index, int value );

protected:
    void resizeEvent(QResizeEvent * event);
    
private:
    static const int ySize;
    static const int xSize;

    Ui::BarDiagramWidget * ui;
    QList<QGraphicsRectItem *> * bars;
    QGraphicsScene * graphicsScene;

    void createGraphicsScene();
    void drawPercentageLines();
};

#endif // BARDIAGRAMWIDGET_H
