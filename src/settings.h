/***************************************************************************
 *   Copyright (C) 2014  Paul-Christian Volkmer
 *   <paul-christian.volkmer@mni.thm.de>
 *
 *   This file is part of ARSnova Overlay.
 *
 *   ARSnova Overlay is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   ARSnova Overlay is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with ARSnova Overlay.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QUrl>
#include <memory>

class Settings : public QObject {

    Q_OBJECT

public:
    enum WidgetPosition {
        BOTTOM_RIGHT,
        BOTTOM_LEFT,
        TOP_LEFT,
        TOP_RIGHT
    };

    static std::shared_ptr<Settings> instance();

    ~Settings();

    Settings::WidgetPosition widgetPosition();
    void setWidgetPosition ( Settings::WidgetPosition widgetPosition );

    QUrl serverUrl();
    void setServerUrl ( QUrl serverUrl );

    int screen();
    void setScreen ( int screen );

private:
    Settings();
    QSettings * qsettings;
    static std::shared_ptr<Settings> _instance;

signals:
    void settingsChanged();

};

#endif // SETTINGS_H
