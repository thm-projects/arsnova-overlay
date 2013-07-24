#ifndef EMOTEDIAGRAMWIDGET_H
#define EMOTEDIAGRAMWIDGET_H

#include <QtGui>
#include "ui_emotediagramwidget.h"
#include "feedbackresponse.h"

class EmoteDiagramWidget : public QWidget, Ui::EmoteDiagramWidget {
    Q_OBJECT

public:
    explicit EmoteDiagramWidget ( QWidget* parent = 0, Qt::WindowFlags f = 0 );
    virtual ~EmoteDiagramWidget();
    /** Returns user interface of this widget.
     * This method is helpfull if someone needs direct access to the
     * user interface itself e.g. testing.
     * @return User interface
     */
    const Ui::EmoteDiagramWidget * const getUi();
    void updateFromResponse ( FeedbackResponse response );

private:
    Ui::EmoteDiagramWidget * ui;

    void resizeEvent ( QResizeEvent * event );
};

#endif // EMOTEDIAGRAMWIDGET_H
