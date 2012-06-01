#include "loginwidget.h"

LoginWidget::LoginWidget ( QWidget* parent, Qt::WindowFlags f )
    : QWidget ( parent, f ), _ui ( new Ui::LoginWidget() ) {
    _ui->setupUi ( this );
}

const Ui::LoginWidget * const LoginWidget::getUi() {
    return this->_ui;
}

QString LoginWidget::text() {
    return _ui->sessionIdEdit->text();
}

void LoginWidget::setText ( QString text ) {
    _ui->sessionIdEdit->setText ( text );
}

void LoginWidget::clear() {
    _ui->sessionIdEdit->clear();
}

void LoginWidget::on_sessionIdEdit_returnPressed() {
    emit this->returnPressed();
}

void LoginWidget::on_exitButton_clicked() {
    emit this->exitButtonClicked();
}

void LoginWidget::on_loginButton_clicked() {
    emit this->loginButtonClicked();
}
