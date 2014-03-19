#ifndef QRCODEWIDGET_H
#define QRCODEWIDGET_H

#include <QtGui>
#include "ui_qrcodewidget.h"
#include "qrcodegenerator.h"
#include "sessioncontext.h"

class QRCodeWidget : public QWidget, Ui::QRCodeWidget {
    Q_OBJECT

public:
    explicit QRCodeWidget ( SessionContext * context, QStackedWidget * parent = 0, Qt::WindowFlags f = 0 );
    virtual ~QRCodeWidget();
    void setFullscreen ( bool fullscreen, int screen = -1 );
    /** Returns user interface of this widget.
     * This method is helpfull if someone needs direct access to the
     * user interface itself e.g. testing.
     * @return User interface
     */
    const Ui::QRCodeWidget * const getUi();
    virtual void show();
    QRCodeWidget * getFullscreenWidget() const;

public slots:
    virtual bool close();

private:
    enum Transformation {
        NONE,
        TOP,
        BOTTOM,
        LEFT,
        RIGHT
    };

    Ui::QRCodeWidget * _ui;
    void adjustSize();
    QSize neededQRCodeSize();
    QString neededFontSize();
    void setUrl ( QUrl url );
    SessionContext * _sessionContext;
    QStackedWidget * parentBackup;
    QRCodeWidget * fullscreenWidget;

private slots:
    void onSessionChanged();
    void onFullscreenButtonToggled ( bool );
    void onFullscreenWidgetClosed();

signals:
    void closed();
};

#endif // QRCODEWIDGET_H
