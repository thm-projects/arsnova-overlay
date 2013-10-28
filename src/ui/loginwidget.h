#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QtGui>
#include <QtDeclarative>

/** This class provides the ArsNova login widget as a Qt Widget
 * @author Paul-Christian Volkmer <paul-christian.volkmer@mni.thm.de>
 */
class LoginWidget : public QDeclarativeView {
    Q_OBJECT

public:
    explicit LoginWidget ( QWidget* parent = 0, Qt::WindowFlags f = 0 );
    virtual ~LoginWidget();
    QString text();
    void setText ( QString text );
    void clear();
    /** Returns user interface of this widget.
     * This method is helpfull if someone needs direct access to the
     * user interface itself e.g. testing.
     * @return User interface
     */
    QGraphicsScene * const getUi();

private:
    QDeclarativeItem * item;

private slots:
    void on_exitButton_clicked();
    void on_loginButton_clicked();

signals:
    void exitButtonClicked();
    void loginButtonClicked();
};

#endif // LOGINWIDGET_H
