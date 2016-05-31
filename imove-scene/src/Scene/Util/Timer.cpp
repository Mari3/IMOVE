//
// Created by Wouter Posdijk on 12/05/16.
//

#include "Timer.h"

Timer::Timer(float timeInSeconds, bool autoRestart) : startTime(timeInSeconds), time(timeInSeconds), autoRestart(autoRestart)
{
}

bool Timer::update(float dt)
{
    time -= dt;
    if(time <= 0)
    {
        if(autoRestart)time += startTime;
        return true;
    }
    return false;
}

void Timer::restart()
{
    time = startTime;
}

void Timer::restart(float newTime)
{
    startTime = newTime;
    time = newTime;
}








