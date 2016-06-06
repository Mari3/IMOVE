//
// Created by Wouter Posdijk on 12/05/16.
//

#include <cmath>
#include "LightTrail.h"

LightTrail::LightTrail(Vector2 location, Vector2 speed, float hue, float lifespan) :
    location(location),
    speed(speed),
    hue(hue),
    lifespan(lifespan),
    prevLocation(location),
    prevPrevLocation(location)
{
    hasLifespan = lifespan > 0;
}

void LightTrail::applyForce(Vector2 force, float dt, float speedCap, bool sidesEnabled,
    unsigned int screenWidth, unsigned int screenHeight) {

    prevPrevLocation = prevLocation;
    prevLocation = location;

    //Increase the speed based on the force and delta time
    speed += force*dt;

    //Cap the speed at 500
    if(speed.size() > speedCap){
        speed = speed/speed.size()*speedCap;
    }

    //Increase the location based on the speed and delta time
    location += speed*dt;

    //Bounce off the edges of the screen
    if(sidesEnabled) {
        if (location.x < 0) {
            location.x = 0;
            speed.x *= -1;
        } else if (location.x > screenWidth) {
            location.x = screenWidth;
            speed.x *= -1;
        }
        if (location.y < 0) {
            location.y = 0;
            speed.y *= -1;
        } else if (location.y > screenHeight) {
            location.y = screenHeight;
            speed.y *= -1;
        }
    }
}

Vector2 LightTrail::getLocation() {
    return location;
}

Vector2 LightTrail::getSpeed() {
    return speed;
}

bool LightTrail::tick(float dt) {
    return hasLifespan && lifespan.update(dt);
}

float LightTrail::getAngle() {
    Vector2 diff = location-prevLocation;
    return static_cast<float>(atan2f(diff.y,diff.x)*180.f/M_PI);
}

Vector2 LightTrail::getSize() {
    float sp = speed.size()/340.f*2.f;


    Vector2 diff = location-prevLocation;
    diff = diff/diff.size();
    Vector2 prevDiff = prevLocation-prevPrevLocation;
    prevDiff = prevDiff/prevDiff.size();

    if(sp<1) sp = 1;
    float th = 1.f/sp;

    float angle = acosf(diff.x*prevDiff.x+diff.y*prevDiff.y);
    if(angle > .2*M_PI){
        //th *= 2;
        //TODO do something with quick turning
    }

    return Vector2(sp,th);
}













