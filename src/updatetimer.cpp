#include "updatetimer.h"

int UpdateTimer::tickDuration = 1000;

UpdateTimer::UpdateTimer() : qtimer ( std::unique_ptr<QTimer> ( new QTimer() ) ) {
    qtimer->start ( tickDuration );
    this->ticks = 0;
    connect ( qtimer.get(), SIGNAL ( timeout() ), this, SLOT ( update() ) );
}

UpdateTimer::~UpdateTimer() {}

void UpdateTimer::update() {
    emit tick ( this->ticks++ );
}

void UpdateTimer::reset() {
    this->ticks = 0;
}
