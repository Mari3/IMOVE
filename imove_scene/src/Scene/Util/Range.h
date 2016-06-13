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
public:
	Range();
    Range(float start, float end, RangeRandom* random, bool bounds=false, float lowerBound=0.f, float upperBound=360.f);
    Range(float start, float end, bool bounds=false, float lowerBound=0.f, float upperBound=360.f);
    float start, end;
    RangeRandom* random;
    bool bounds;
		float lowerBound, upperBound;
    void operator+=(const float& f);
    float drawRandom();
    float getCenter();
    bool contains(float f) const;
    void fixBounds();
};


#endif //IMOVE_RANGE_H
