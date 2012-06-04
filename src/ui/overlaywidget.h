#ifndef OVERLAYWIDGET_H
#define OVERLAYWIDGET_H

#include <QtGui>
#include <QtNetwork>
#include <QtScript>

#include "ui_overlaywidget.h"
#include "../updatetimer.h"
#include "abstractconnection.h"
#include "sessionresponse.h"
#include "understandingresponse.h"
#include "svglogo.h"
#include "qrcodewidget.h"

class OverlayWidget : public QWidget, Ui::OverlayWidget {
    Q_OBJECT

public:
    explicit OverlayWidget ( AbstractConnection * connection, QWidget* parent = 0, Qt::WindowFlags f = 0 );
    virtual ~OverlayWidget();
    const Ui::OverlayWidget * const getUi();

private:
    Ui::OverlayWidget * ui;
    UpdateTimer * updateTimer;

    AbstractConnection * connection;
    QString sessionId;
    int loggedInUsers;
    int latestUnderstandingResponses;
    QRCodeWidget * qrcodewidget;

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
    void connectSignals();

private slots:
    bool close();

    void sessionLogin();
    void updateHttpResponse ( int ticks );
    void showSessionIdForm();
    void makeTransparent ( bool enabled );
    void makeFullscreen ( bool enabled );
    void switchView ( bool coloredLogoView );
    void showQRCode ( bool enabled );

    void onSessionResponse ( SessionResponse response );
    void onUnderstandingResponse ( UnderstandingResponse response );
    void onLoggedInResponse ( LoggedInResponse response );
};

#endif // OVERLAYWIDGET_H
