//
// Created by Wouter Posdijk on 12/05/16.
//

#include <random>
#include "Range.h"

Range::Range(float start, float end, bool bounds, float lowerBound, float upperBound) :
    start(start),end(end),bounds(bounds),lowerBound(lowerBound),upperBound(upperBound)
{
    if(bounds){
        fixBounds();
    }
}

void Range::fixBounds() {
    while(start < lowerBound)start += upperBound-lowerBound;
    while(end < lowerBound)end += upperBound-lowerBound;
    while(start > upperBound)start -= upperBound-lowerBound;
    while(end > upperBound)end -= upperBound-lowerBound;
}

void Range::operator+=(const float &f) {
    start += f;
    end += f;
    if(bounds)fixBounds();
}

float Range::drawRandom() {
    if(start < end) {
        return start + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (end - start)));
    }else if(start == end){
        return start;
    }else{
        if(!bounds)return start;//TODO throw error
        else{
            float hi = upperBound+end-lowerBound;
            float val = start + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - start)));
            if(val > upperBound)val -= upperBound-lowerBound;
            return val;
        }
    }
}

bool Range::contains(float f) {
    if(end > start)
        return f > start && f < end;
    if(start == end)
        return f == start;

    return (f > start && f < upperBound) || (f < end && f > lowerBound);
}









