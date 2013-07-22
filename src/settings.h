/***************************************************************************
 *   Copyright (C) 2013  Paul-Christian Volkmer
 *   <paul-christian.volkmer@mni.thm.de>
 *
 *   This file is part of ARSnovaDesktop.
 *
 *   ARSnovaDesktop is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   ARSnovaDesktop is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with ARSnovaDesktop.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QUrl>
#include <memory>

class Settings {
public:
    static std::shared_ptr<Settings> instance();

    enum WidgetPosition {
        BOTTOM_RIGHT,
        BOTTOM_LEFT,
        TOP_LEFT,
        TOP_RIGHT
    };

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

};

#endif // SETTINGS_H
