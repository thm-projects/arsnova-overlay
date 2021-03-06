#ifndef LOGODIAGRAMWIDGET_H
#define LOGODIAGRAMWIDGET_H

#include <QtGui>
#include "ui_logodiagramwidget.h"
#include "svglogo.h"
#include "feedbackresponse.h"

class LogoDiagramWidget : public QWidget, Ui::LogoDiagramWidget {
    Q_OBJECT

public:
    explicit LogoDiagramWidget ( QWidget* parent = 0, Qt::WindowFlags f = 0 );
    virtual ~LogoDiagramWidget();
    /** Returns user interface of this widget.
     * This method is helpfull if someone needs direct access to the
     * user interface itself e.g. testing.
     * @return User interface
     */
    const Ui::LogoDiagramWidget * const getUi();
    void updateFromResponse ( FeedbackResponse response );

private:
    Ui::LogoDiagramWidget * ui;
    SvgLogo * svgLogo;

    void resizeEvent ( QResizeEvent * event );
    void mousePressEvent ( QMouseEvent * event );

signals:
    void clicked ( bool checked = false );
};

#endif // LOGODIAGRAMWIDGET_H
