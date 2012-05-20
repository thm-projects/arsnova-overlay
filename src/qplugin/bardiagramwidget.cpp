#include "bardiagramwidget.h"

BarDiagramWidget::BarDiagramWidget ( QWidget* parent, Qt::WindowFlags f )
    : QWidget ( parent, f ), ui ( new BarDiagramWidget() ) {
    ui->setupUi ( this );
}
