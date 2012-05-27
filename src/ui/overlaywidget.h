#ifndef OVERLAYWIDGET_H
#define OVERLAYWIDGET_H

#include <QtGui>
#include <QtNetwork>
#include <QtScript>
#include "ui_overlaywidget.h"

#include "../updatetimer.h"
#include "httpconnection.h"

#include "sessionresponse.h"
#include "understandingresponse.h"
#include "svglogo.h"

class OverlayWidget : public QWidget, Ui::OverlayWidget {
    Q_OBJECT

public:
    explicit OverlayWidget ( QWidget* parent = 0, Qt::WindowFlags f = 0 );
    const Ui::OverlayWidget * const getUi();

private:
    Ui::OverlayWidget * ui;
    UpdateTimer * updateTimer;

    HttpConnection * httpConnection;
    QString sessionId;
    int loggedInUsers;
    int latestUnderstandingResponses;

    static const int httpUpdateInterval;
    static const int ySize;
    static const int xSize;
    void moveToBottomRightEdge();

    enum VisibileViewType {
        LOGIN_VIEW,
        BAR_VIEW,
        COLORED_LOGO_VIEW
    };

    void setVisibleViewType ( VisibileViewType type );

private slots:
    void sessionLogin();
    void updateHttpResponse ( int ticks );
    void showSessionIdForm();
    void makeTransparent ( bool enabled );
    void makeFullscreen ( bool enabled );
    void switchView ( bool coloredLogoView );

    void onSessionResponse ( SessionResponse response );
    void onUnderstandingResponse ( UnderstandingResponse response );
    void onLoggedInResponse ( LoggedInResponse response );
};

#endif // OVERLAYWIDGET_H
