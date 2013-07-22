#include "settingswidget.h"

SettingsWidget::SettingsWidget ( SessionContext * context, QWidget* parent, Qt::WindowFlags f )
    : QWidget ( parent, f ),
      _ui ( new Ui::SettingsWidget() ),
      _context ( context ) {

    _ui->setupUi ( this );

    for ( int i = 1; i < QApplication::desktop()->screenCount(); i++ ) {
        this->_ui->screenComboBox->addItem ( QString::number ( i ) );
    }

    this->_ui->serverUriLineEdit->setText ( _context->getSettings()->serverUrl().toString() );

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
    _context->getSettings()->setServerUrl ( QUrl ( this->_ui->serverUriLineEdit->text() ) );
    _context->getSettings()->setWidgetPosition ( ( SessionContext::WidgetPosition ) this->_ui->widgetPositionComboBox->currentIndex() );
    _context->getSettings()->setScreen ( this->_ui->screenComboBox->currentIndex() );

    QMessageBox::about ( this, "Restart required", "Please restart this application to enable new settings" );
}

void SettingsWidget::onSettingsRejected() {
    this->_ui->serverUriLineEdit->setText ( _context->getSettings()->serverUrl().toString() );
    this->_ui->widgetPositionComboBox->setCurrentIndex ( (int) _context->getSettings()->widgetPosition() );
    this->_ui->screenComboBox->setCurrentIndex ( _context->getSettings()->screen() );
}
