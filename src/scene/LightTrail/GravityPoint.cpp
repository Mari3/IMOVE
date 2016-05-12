//
// Created by Wouter Posdijk on 12/05/16.
//

#include "GravityPoint.h"

GravityPoint::GravityPoint(Vector2 location, Range hue, float gravity) :
    location(location), hue(hue), gravity(gravity)
{

}

const Vector2 &GravityPoint::getLocation() const {
    return location;
}

const Range &GravityPoint::getHue() const {
    return hue;
}

float GravityPoint::getGravity() const {
    return gravity;
}