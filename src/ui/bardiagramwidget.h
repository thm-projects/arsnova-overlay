#ifndef BARDIAGRAMWIDGET_H
#define BARDIAGRAMWIDGET_H

#include <QtGui>
#include <QtDeclarative>
#include <memory>
#include "feedbackresponse.h"

class BarDiagramWidget : public QDeclarativeView {
    Q_OBJECT

public:
    explicit BarDiagramWidget ( QWidget* parent = 0, Qt::WindowFlags f = 0 );
    virtual ~BarDiagramWidget();

    QGraphicsScene * const getUi();
    void updateGraphicsBar ( int index, int value );
    void updateFromResponse ( FeedbackResponse response );

private:
    QDeclarativeItem * item;
    
    void mousePressEvent(QMouseEvent * event);
    
signals:
    void clicked(bool checked = false);
};

#endif // BARDIAGRAMWIDGET_H
