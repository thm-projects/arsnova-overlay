#include "logodiagramwidget.h"

LogoDiagramWidget::LogoDiagramWidget ( QWidget * parent, Qt::WindowFlags f )
    : QWidget ( parent, f ), ui ( new Ui::LogoDiagramWidget() ) {
    ui->setupUi ( this );

    this->svgLogo = new SvgLogo();
    this->updateFromResponse ( UnderstandingResponse ( 0,0,0,0 ) );
}

LogoDiagramWidget::~LogoDiagramWidget() {
    delete this->svgLogo;
}

const Ui::LogoDiagramWidget*const LogoDiagramWidget::getUi() {
    return this->ui;
}

void LogoDiagramWidget::updateFromResponse ( UnderstandingResponse response ) {
    this->svgLogo->updateFromResponse ( response );
    ui->logoWidget->load ( this->svgLogo->toXml() );
}

void LogoDiagramWidget::resizeEvent ( QResizeEvent* event ) {
    int minEdgeSize = this->size().height() < this->size().width()
                      ? this->size().height()
                      : this->size().width();
    QSize size ( 8, 8 );
    size.scale ( minEdgeSize, minEdgeSize, Qt::KeepAspectRatio );
    ui->logoWidget->resize ( size );

    this->setContentsMargins (
        ( this->width() - minEdgeSize ) / 2,
        0,
        ( this->width() - minEdgeSize ) / 2,
        0
    );
    QWidget::resizeEvent ( event );
}
