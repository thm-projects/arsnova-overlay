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

#include "sessioncontexttest.h"

SessionContextTest::SessionContextTest() : QObject() {}

void SessionContextTest::initTestCase() {
    connection = new StubConnection();
}

void SessionContextTest::cleanupTestCase() {
    delete sessionContext;
}

void SessionContextTest::testShouldDetectInvalidSessionContext() {
    sessionContext = new SessionContext ( connection );
    QVERIFY ( sessionContext->isValid() == false );
}

void SessionContextTest::testShouldDetectValidSessionContext() {
    sessionContext = new SessionContext ( connection );
    connection->requestSession ( "12345678" );
    QVERIFY ( sessionContext->isValid() == true );
}

void SessionContextTest::testShouldReturnSessionId() {
    sessionContext = SessionContext::create ( connection, "12345678" );
    QVERIFY ( sessionContext->sessionId() == "12345678" );
}

void SessionContextTest::testShouldDetectThatThisSessionIsNotKnown() {
    sessionContext = SessionContext::create ( connection, "" );
    QVERIFY ( sessionContext->isValid() == false );
}

void SessionContextTest::testShouldEmitSessionChangedSignal() {
    QSignalSpy spy ( this->sessionContext, SIGNAL ( sessionChanged() ) );
    connection->requestSession ( "12345678" );
    QVERIFY ( spy.count() == 1 );
}
