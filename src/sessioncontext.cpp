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

#include "sessioncontext.h"

SessionContext::SessionContext ( AbstractConnection * connection )
    : _connection ( connection ), _isValid ( false ) {
    connect ( _connection, SIGNAL ( requestFinished ( UnderstandingResponse ) ), this, SLOT ( onUnderstandingResponse ( UnderstandingResponse ) ) );
    connect ( _connection, SIGNAL ( requestFinished ( SessionResponse ) ), this, SLOT ( onSessionResponse ( SessionResponse ) ) );
}

SessionContext * SessionContext::create ( AbstractConnection * connection, QString sessionKey ) {
    SessionContext * context = new SessionContext ( connection );
    connection->requestSession ( sessionKey );
    return context;
}

QString SessionContext::sessionId() {
    return _sessionId;
}

bool SessionContext::isValid() {
    return _isValid;
}

AbstractConnection * SessionContext::connection() {
    return _connection;
}

void SessionContext::onUnderstandingResponse ( UnderstandingResponse response ) {

}

void SessionContext::onSessionResponse ( SessionResponse response ) {
    if ( !response.sessionId().isEmpty() ) {
        _sessionId = response.sessionId();
        _isValid = true;
    }
}
