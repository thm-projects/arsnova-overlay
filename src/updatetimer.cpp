#include "updatetimer.h"

UpdateTimer::UpdateTimer() : qtimer ( new QTimer() ) {
    qtimer->start ( 1000 );
    this->ticks = 0;
    connect ( qtimer, SIGNAL ( timeout() ), this, SLOT ( update() ) );
}

void UpdateTimer::update() {
    emit tick ( this->ticks++ );
}

void UpdateTimer::reset() {
    this->ticks = 0;
}
