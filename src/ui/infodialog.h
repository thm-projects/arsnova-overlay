#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QtGui>
#include <QtCore>
#include "ui_infodialog.h"
#include "version.h"

class InfoDialog : public QDialog, private Ui::InfoDialog {
    Q_OBJECT

public:
    InfoDialog ( QWidget* parent = 0, Qt::WFlags fl = 0 );
    ~InfoDialog();

public slots:

protected:

protected slots:
    void on_closeButton_clicked();

};

#endif
