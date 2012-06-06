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
