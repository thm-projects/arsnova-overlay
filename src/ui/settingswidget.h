#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QtWidgets>
#include "ui_settingswidget.h"
#include "settings.h"
#include "sessioncontext.h"

class SettingsWidget : public QWidget, Ui::SettingsWidget {
    Q_OBJECT

public:
    explicit SettingsWidget ( SessionContext * context, QWidget* parent = 0, Qt::WindowFlags f = 0 );
    virtual ~SettingsWidget();
    const Ui::SettingsWidget * const getUi();

private:
    Ui::SettingsWidget * _ui;
    SessionContext * _context;

private slots:
    void onSettingsAccepted();
    void onSettingsRejected();

};

#endif // SETTINGSWIDGET_H
