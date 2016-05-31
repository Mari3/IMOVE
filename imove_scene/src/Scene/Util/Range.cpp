//
// Created by Wouter Posdijk on 12/05/16.
//

#include <random>
#include "Range.h"

util::Range::Range(float start, float end, RangeRandom* random, bool bounds, float lowerBound, float upperBound) :
    start(start),
		end(end),
		lowerBound(lowerBound),
		upperBound(upperBound),
		bounds(bounds),
		random(random)
{
    if(bounds)
    {
        fixBounds();
    }
}

void util::Range::fixBounds()
{
    while(start < lowerBound)start += upperBound-lowerBound;
    while(end < lowerBound)end += upperBound-lowerBound;
    while(start > upperBound)start -= upperBound-lowerBound;
    while(end > upperBound)end -= upperBound-lowerBound;
}

void util::Range::operator+=(const float &f)
{
    start += f;
    end += f;
    if(bounds)fixBounds();
}

float util::Range::drawRandom()
{
    return random->next(start,end,bounds,lowerBound,upperBound);
}

bool util::Range::contains(float f)
{
    if(end > start)
        return f > start && f < end;
    if(start == end)
        return f == start;

    return (f > start && f < upperBound) || (f < end && f > lowerBound);
}

util::Range::Range(float start, float end, bool bounds, float lowerBound, float upperBound) :
        Range(start,end,UniformRangeRandom::getInstance(),
              bounds,lowerBound,upperBound)
{

}











