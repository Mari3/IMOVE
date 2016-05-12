//
// Created by Wouter Posdijk on 12/05/16.
//

#include "LightTrail.h"

LightTrail::LightTrail(Vector2 location, Vector2 speed, float hue) :
    location(location),
    speed(speed),
    hue(hue)
{
}

void LightTrail::update(Vector2 force, float dt) {
    speed += force*dt;
    location += speed*dt;
    //TODO check for edges of scene
}

Vector2 LightTrail::getLocation() {
    return location;
}







