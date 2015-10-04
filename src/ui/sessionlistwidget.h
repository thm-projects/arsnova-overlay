#ifndef SESSIONLISTWIDGET_H
#define SESSIONLISTWIDGET_H

#include <QtWidgets/QtWidgets>
#include <QtDeclarative>

class SessionListWidget : public QDeclarativeView  {
    Q_OBJECT

public:
    explicit SessionListWidget ( QWidget* parent = 0 );
    void addSession ( QVariantMap newSession );

private:
    QDeclarativeItem * item;

private slots:
    void onSessionChanged ( QString sessionKey );

signals:
    void sessionChanged ( QString sessionKey );
};

#endif // SESSIONLISTWIDGET_H
