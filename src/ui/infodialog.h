#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QtWidgets>

#include "ui_infodialog.h"
#include "version.h"

class InfoDialog : public QDialog, private Ui::InfoDialog {
    Q_OBJECT

public:
    InfoDialog ( QWidget* parent = 0, Qt::WindowFlags f = 0 );
    ~InfoDialog();

};

#endif
