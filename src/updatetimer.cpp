#include "updatetimer.h"

const int UpdateTimer::updateInterval = 20;

UpdateTimer::UpdateTimer() : qtimer ( new QTimer() ) {
    qtimer->start ( updateInterval * 1000 );
    connect ( qtimer, SIGNAL ( timeout() ), this, SLOT ( update() ) );
}

void UpdateTimer::update() {
    emit tick();
}
