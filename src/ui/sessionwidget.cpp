#include "sessionwidget.h"

SessionWidget::SessionWidget ( QWidget* parent, Qt::WindowFlags f )
    : QWidget ( parent, f ), _ui ( new Ui::SessionWidget() ) {
    _ui->setupUi ( this );
}

const Ui::SessionWidget * const SessionWidget::getUi() {
    return this->_ui;
}
