#ifndef SESSIONWIDGET_H
#define SESSIONWIDGET_H

#include <QtGui>
#include "sessioncontext.h"
#include "ui_sessionwidget.h"

class SessionWidget : public QWidget, Ui::SessionWidget {
    Q_OBJECT

public:
    explicit SessionWidget ( SessionContext * context, QWidget* parent = 0, Qt::WindowFlags f = 0 );
    virtual ~SessionWidget();
    const Ui::SessionWidget * const getUi();

private:
    Ui::SessionWidget * _ui;
    AbstractConnection * connection;
    SessionContext * context;

public slots:
    void onUnderstandingResponse ( FeedbackResponse response );
    void onSessionResponse ( SessionResponse response );
    void onItemClicked ( QString sessionKey );
    void onViewModeChanged();
    
    void onBarDiagramSelected();
    void onLogoDiagramSelected();
    void onEmoteDiagramSelected();

signals:
    void sessionClicked ( QString sessionKey );
};

#endif // SESSIONWIDGET_H
