/***************************************************************************
 *   Copyright (C) 2012  Paul-Christian Volkmer
 *   <paul-christian.volkmer@mni.thm.de>
 *
 *   This file is part of ARSnovawidget.
 *
 *   ARSnovawidget is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   ARSnovawidget is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with ARSnovawidget.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifndef SESSIONWIDGETTEST_H
#define SESSIONWIDGETTEST_H

#include <QtTestGui>
#include <QTest>
#include "ui/sessionwidget.h"
#include "stubconnection.h"
#include "sessioncontext.h"

class SessionWidgetTest : public QObject {

    Q_OBJECT

public:
    explicit SessionWidgetTest ( QObject* parent = 0 );

private:
    SessionWidget * sessionWidget;
    SessionContext * context;
    AbstractConnection * connection;

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testShouldAddSessionToSessionList();
    void testShouldNotAddSessionTwice();
    void testShouldDetectResponseError();
};

#endif // SESSIONWIDGETTEST_H
