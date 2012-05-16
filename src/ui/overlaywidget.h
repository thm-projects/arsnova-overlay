#ifndef OVERLAYWIDGET_H
#define OVERLAYWIDGET_H

#include <QtGui>
#include <QtNetwork>
#include <QtScript>
#include "ui_overlaywidget.h"

#include "../updatetimer.h"
#include "httpconnection.h"

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
    HttpConnection * httpConnection;
    QString sessionId;
    QString styleSheetBackup;
    int loggedInUsers;
    int latestUnderstandingResponses;

    static const int httpUpdateInterval;
    static const int ySize;
    static const int xSize;
    void createGraphicsScene();
    void updateGraphicsBar ( int index, int value );
    void moveToBottomRightEdge();

private slots:
    void sessionLogin();
    void updateHttpResponse ( int ticks );
    void updateGraphicsScene(HttpConnection::RequestType type, QScriptValue * response);
    void drawPercentageLines();
    void showSessionIdForm();
    void makeTransparent(bool enabled);
    void makeFullscreen(bool enabled);
};

#endif // OVERLAYWIDGET_H
