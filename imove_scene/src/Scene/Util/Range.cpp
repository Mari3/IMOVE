//
// Created by Wouter Posdijk on 12/05/16.
//

#include <assert.h>
#include <random>
#include "Range.h"

util::Range::Range(float start, float end, RangeRandom* random, bool bounds, float lowerBound, float upperBound) :
    start(start),
		end(end),
		random(random),
		bounds(bounds),
		lowerBound(lowerBound),
		upperBound(upperBound)
{
    if(bounds)
    {
        assert(upperBound > lowerBound);
				fixBounds();
    }else
		{
		    assert(end > start);
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

bool util::Range::contains(float f) const
{
    if(end > start)
        return f >= start && f <= end;
    if(start == end)
        return f == start;

    return (f >= start && f <= upperBound) || (f <= end && f >= lowerBound);
}

util::Range::Range(float start, float end, bool bounds, float lowerBound, float upperBound) :
        Range(start,end,UniformRangeRandom::getInstance(),
              bounds,lowerBound,upperBound)
{

}

float util::Range::getCenter() {
    if(end > start)
        return (start+end)/2.f;
    if(end == start)
        return start;

    float diff = end-lowerBound + upperBound-start;
    float center = start+diff/2.f;
    if(center>upperBound)
        center -= upperBound-lowerBound;
    return center;
}













