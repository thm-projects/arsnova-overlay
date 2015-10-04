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

#include "sessionwidgettest.h"
#include <qsignalspy.h>

SessionWidgetTest::SessionWidgetTest ( QObject* parent ) : QObject ( parent ) {}

void SessionWidgetTest::initTestCase() {
    this->connection = new StubConnection();
    this->context = new SessionContext ( this->connection );
    this->sessionWidget = new SessionWidget ( this->context );
    this->sessionWidget->show();
}

void SessionWidgetTest::cleanupTestCase() {
    delete this->sessionWidget;
    delete this->context;
    delete this->connection;
}

void SessionWidgetTest::testShouldAddSessionToSessionList() {
    this->context->connection()->requestSession ( "12345678" );
}

void SessionWidgetTest::testShouldNotAddSessionTwice() {
    this->context->connection()->requestSession ( "12345678" );
}

void SessionWidgetTest::testShouldDetectResponseError() {
    QSignalSpy spy ( this->context->connection(), SIGNAL ( requestError() ) );
    this->context->connection()->requestSession ( QString() );

    QCOMPARE ( spy.count(), 1 );
}
