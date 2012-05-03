#ifndef OVERLAYWIDGET_H
#define OVERLAYWIDGET_H

#include <QtGui>
#include <QtNetwork>
#include <QtScript>
#include "ui_overlaywidget.h"

#include "../updatetimer.h"

class OverlayWidget : public QWidget, Ui::OverlayWidget {
    Q_OBJECT

public:
    explicit OverlayWidget ( QWidget* parent = 0, Qt::WindowFlags f = 0 );

private:
    Ui::OverlayWidget * ui;
    QGraphicsScene * graphicsScene;
    UpdateTimer * updateTimer;
    QList<QGraphicsRectItem *> * bars;

    QHttp * httpClient;
    QString sessionId;

    static const int ySize;

    void createGraphicsScene();
    void updateGraphicsBar ( int index, int value );

private slots:
    void updateHttpResponse();
    void updateGraphicsScene();
    void drawPercentageLines();
};

#endif // OVERLAYWIDGET_H
