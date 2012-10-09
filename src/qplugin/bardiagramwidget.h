#ifndef BARDIAGRAMWIDGET_H
#define BARDIAGRAMWIDGET_H

#include <QtGui>
#include "ui_bardiagramwidget.h"
#include "understandingresponse.h"

class BarDiagramWidget : public QWidget, Ui::BarDiagramWidget {
    Q_OBJECT

public:
    explicit BarDiagramWidget ( QWidget* parent = 0, Qt::WindowFlags f = 0 );
    virtual ~BarDiagramWidget();
    /** Returns user interface of this widget.
     * This method is helpfull if someone needs direct access to the
     * user interface itself e.g. testing.
     * @return User interface
     */
    const Ui::BarDiagramWidget * const getUi();
    void updateGraphicsBar ( int index, int value );
    void updateFromResponse ( UnderstandingResponse response );

protected:
    void resizeEvent ( QResizeEvent * event );

private:
    class BarDiagramWidgetPrivate;
    BarDiagramWidgetPrivate * _private;

    Ui::BarDiagramWidget * ui;

    static const int ySize;
    static const int xSize;
};

#endif // BARDIAGRAMWIDGET_H
