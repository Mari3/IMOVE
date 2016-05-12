//
// Created by Wouter Posdijk on 12/05/16.
//

#ifndef IMOVE_LIGHTSOURCE_H
#define IMOVE_LIGHTSOURCE_H


#include "../../shared/Vector2.h"
#include "../../shared/Range.h"
#include "LightTrail.h"

class LightSource {
private:
    Vector2 location;
    Range hue,angle,speed;
public:
    LightSource(Vector2 location, Range hue, Range angle, Range speed);
    LightTrail sendOut();
    Vector2 getLocation();
    Range getHue();
};


#endif //IMOVE_LIGHTSOURCE_H
