#include "updatetimer.h"

int UpdateTimer::tickDuration = 1000;

UpdateTimer::UpdateTimer() : qtimer ( new QTimer() ) {
    qtimer->start ( tickDuration );
    this->ticks = 0;
    connect ( qtimer, SIGNAL ( timeout() ), this, SLOT ( update() ) );
}

UpdateTimer::~UpdateTimer() {
    delete qtimer;
}

void UpdateTimer::update() {
    emit tick ( this->ticks++ );
}

void UpdateTimer::reset() {
    this->ticks = 0;
}
