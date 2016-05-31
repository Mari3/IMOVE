//
// Created by Wouter Posdijk on 27/05/16.
//

#ifndef IMOVE_UNIFORMRANGERANDOM_H
#define IMOVE_UNIFORMRANGERANDOM_H


#include "RangeRandom.h"

class UniformRangeRandom : public RangeRandom {
private:
    static UniformRangeRandom* _instance;
public:
    float next(float start, float end, bool bounds, float lowerBound, float upperBound) override;
    static UniformRangeRandom* getInstance();
};


#endif //IMOVE_UNIFORMRANGERANDOM_H
