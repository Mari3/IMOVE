//
// Created by Wouter Posdijk on 12/05/16.
//

#include "Timer.h"

Timer::Timer(float timeInSeconds) : startTime(timeInSeconds), time(timeInSeconds) {
}

bool Timer::update(float dt) {
    time -= dt;
    return time <= 0;
}

void Timer::restart() {
    time = startTime;
}

void Timer::restart(float newTime) {
    startTime = newTime;
    time = newTime;
}








