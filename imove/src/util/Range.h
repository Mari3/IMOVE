//
// Created by Wouter Posdijk on 12/05/16.
//

#ifndef IMOVE_RANGE_H
#define IMOVE_RANGE_H

#include "RangeRandom.h"
#include "UniformRangeRandom.h"

namespace util
{
class Range;
}

class util::Range
{
private:
    float start, end, lowerBound, upperBound;
    bool bounds;
    void fixBounds();
    RangeRandom* random;
public:
    Range(float start, float end, RangeRandom* random, bool bounds=false, float lowerBound=0.f, float upperBound=360.f);
    Range(float start, float end, bool bounds=false, float lowerBound=0.f, float upperBound=360.f);
    void operator+=(const float& f);
    float drawRandom();
    bool contains(float f);
};


#endif //IMOVE_RANGE_H
