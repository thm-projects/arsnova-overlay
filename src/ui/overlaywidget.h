#ifndef OVERLAYWIDGET_H
#define OVERLAYWIDGET_H

#include <QtGui>
#include <QtNetwork>
#include <QtScript>

#include "ui_overlaywidget.h"
#include "../updatetimer.h"
#include "sessioncontext.h"
#include "sessionresponse.h"
#include "feedbackresponse.h"
#include "svglogo.h"
#include "qrcodewidget.h"

class OverlayWidget : public QWidget, Ui::OverlayWidget {
    Q_OBJECT

public:
    explicit OverlayWidget ( SessionContext * context, QWidget * parent = 0, Qt::WindowFlags f = 0 );
    virtual ~OverlayWidget();
    /** Returns user interface of this widget.
     * This method is helpfull if someone needs direct access to the
     * user interface itself e.g. testing.
     * @return User interface
     */
    const Ui::OverlayWidget * const getUi();
    virtual void show();

private:
    Ui::OverlayWidget * ui;
    UpdateTimer * updateTimer;

    AbstractConnection * connection;
    QString sessionId;
    int loggedInUsers;
    int latestUnderstandingResponses;
    QRCodeWidget * qrcodewidget;
    SessionContext * context;

    static const int httpUpdateInterval;
    static const int ySize;
    static const int xSize;
    void moveToBottomRightEdge ( int screen = -1 );
    void connectSignals();

public slots:
    bool close();
    void onSessionResponse ( SessionResponse response );
    void onFeedbackResponse ( FeedbackResponse response );
    void onLoggedInResponse ( LoggedInResponse response );

private slots:
    void updateHttpResponse ( int ticks );
    void makeTransparent ( bool enabled );
    void setVisibleViewType ( SessionContext::ViewType type );
};

#endif // OVERLAYWIDGET_H
