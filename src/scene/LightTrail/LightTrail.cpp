//
// Created by Wouter Posdijk on 12/05/16.
//

#include "LightTrail.h"

#define SW 2500
#define SH 1600

LightTrail::LightTrail(Vector2 location, Vector2 speed, float hue) :
    location(location),
    speed(speed),
    hue(hue)
{
}

void LightTrail::update(Vector2 force, float dt) {
    speed += force*dt;

    if(speed.size() > 500){
        speed = speed/speed.size()*500;
    }

    location += speed*dt;
    //TODO check for edges of scene
    if(location.x < 0){
        location.x=0;
        speed.x *= -1;
    }else if(location.x > SW){
        location.x = SW;
        speed.x *= -1;
    }
    if(location.y < 0){
        location.y = 0;
        speed.y *= -1;
    }
    else if(location.y > SH){
        location.y = SH;
        speed.y *= -1;
    }
}

Vector2 LightTrail::getLocation() {
    return location;
}

Vector2 LightTrail::getSpeed() {
    return speed;
}







