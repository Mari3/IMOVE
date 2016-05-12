//
// Created by Wouter Posdijk on 12/05/16.
//

#ifndef IMOVE_TIMER_H
#define IMOVE_TIMER_H


class Timer {
private:
    float startTime, time;
public:
    Timer(float timeInSeconds);
    bool update(float dt);
    void restart();
    void restart(float newTime);
};


#endif //IMOVE_TIMER_H
