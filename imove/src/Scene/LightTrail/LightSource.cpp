//
// Created by Wouter Posdijk on 12/05/16.
//

#include <cmath>
#include "LightSource.h"

#define PI 3.14159265358979323846

LightSource::LightSource(Vector2 location, util::Range hue, util::Range angle, util::Range speed) :
    location(location), hue(hue), angle(angle), speed(speed)
{

}

LightTrail* LightSource::sendOut() {
    float trailHue = hue.drawRandom();
    float trailSpeed = speed.drawRandom();
    float trailAngle = angle.drawRandom();

    //Create speed vector from speed and angle
    Vector2 trailSpeedVector(trailSpeed*static_cast<float>(cos(trailAngle/180.f*PI)),trailSpeed*static_cast<float>(sin(trailAngle/180.f*PI)));

    return new LightTrail(location,trailSpeedVector,trailHue);
}

Vector2 LightSource::getLocation() {
    return location;
}

util::Range LightSource::getHue() {
    return hue;
}







