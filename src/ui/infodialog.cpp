#include "infodialog.h"

InfoDialog::InfoDialog ( QWidget* parent, Qt::WFlags fl )
        : QDialog ( parent, fl ), Ui::InfoDialog() {
    setupUi ( this );
    this->versionLabel->setText ( QString(VERSION_MAJOR) +"." + QString(VERSION_MINOR) + "." + QString(VERSION_PATCH) );
}

InfoDialog::~InfoDialog() {
}
