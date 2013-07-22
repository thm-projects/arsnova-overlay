#include "settingswidget.h"

SettingsWidget::SettingsWidget ( SessionContext * context, QWidget * parent, Qt::WindowFlags f )
    : QWidget ( parent, f ),
      _ui ( new Ui::SettingsWidget() ),
      _context ( context ) {

    _ui->setupUi ( this );

    for ( int i = 1; i < QApplication::desktop()->screenCount(); i++ ) {
        this->_ui->screenComboBox->addItem ( QString::number ( i ) );
    }

    this->_ui->serverUriLineEdit->setText ( Settings::instance()->serverUrl().toString() );
    this->_ui->widgetPositionComboBox->setCurrentIndex ( Settings::instance()->widgetPosition() );
    this->_ui->screenComboBox->setCurrentIndex ( Settings::instance()->screen() );

    connect ( this->_ui->buttonBox, SIGNAL ( accepted() ), this, SLOT ( onSettingsAccepted() ) );
    connect ( this->_ui->buttonBox, SIGNAL ( rejected() ), this, SLOT ( onSettingsRejected() ) );
}

SettingsWidget::~SettingsWidget() {
    delete this->_ui;
}

const Ui::SettingsWidget * const SettingsWidget::getUi() {
    return this->_ui;
}

void SettingsWidget::onSettingsAccepted() {
    Settings::instance()->setServerUrl ( QUrl ( this->_ui->serverUriLineEdit->text() ) );
    Settings::instance()->setWidgetPosition ( ( Settings::WidgetPosition ) this->_ui->widgetPositionComboBox->currentIndex() );
    Settings::instance()->setScreen ( this->_ui->screenComboBox->currentIndex() );

    QMessageBox::about ( this, "Restart required", "Please restart this application to enable new settings" );
}

void SettingsWidget::onSettingsRejected() {
    this->_ui->serverUriLineEdit->setText ( Settings::instance()->serverUrl().toString() );
    this->_ui->widgetPositionComboBox->setCurrentIndex ( ( int ) Settings::instance()->widgetPosition() );
    this->_ui->screenComboBox->setCurrentIndex ( Settings::instance()->screen() );
}
