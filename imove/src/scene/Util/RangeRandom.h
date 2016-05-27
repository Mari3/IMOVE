//
// Created by Wouter Posdijk on 27/05/16.
//

#ifndef IMOVE_RANGERANDOM_H
#define IMOVE_RANGERANDOM_H


class RangeRandom {
public:
    virtual float next(float start, float end, bool bounds, float lowerBound, float upperBound) = 0;

};


#endif //IMOVE_RANGERANDOM_H
