#ifndef LOGODIAGRAMWIDGET_H
#define LOGODIAGRAMWIDGET_H

#include <QtGui>
#include "ui_logodiagramwidget.h"
#include "svglogo.h"
#include "understandingresponse.h"

class LogoDiagramWidget : public QWidget, Ui::LogoDiagramWidget {
    Q_OBJECT

public:
    explicit LogoDiagramWidget ( QWidget* parent = 0, Qt::WindowFlags f = 0 );
    virtual ~LogoDiagramWidget();
    const Ui::LogoDiagramWidget * const getUi();
    void updateFromResponse(UnderstandingResponse response);
    
private:
    Ui::LogoDiagramWidget * ui;
    SvgLogo * svgLogo;
};

#endif // LOGODIAGRAMWIDGET_H
