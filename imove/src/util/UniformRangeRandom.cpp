//
// Created by Wouter Posdijk on 27/05/16.
//

#include <cstdlib>
#include "UniformRangeRandom.h"

UniformRangeRandom* UniformRangeRandom::_instance;

float UniformRangeRandom::next(float start, float end, bool bounds, float lowerBound, float upperBound) {
    if(start < end)
    {
        return start + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (end - start)));
    }
    else if(start == end)
    {
        return start;
    }
    else
    {
        if(!bounds)return start;//TODO throw error
        else
        {
            float hi = upperBound+end-lowerBound;
            float val = start + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - start)));
            if(val > upperBound)val -= upperBound-lowerBound;
            return val;
        }
    }
}

UniformRangeRandom *UniformRangeRandom::getInstance() {
    if(!_instance)
        _instance = new UniformRangeRandom();
    return _instance;
}

