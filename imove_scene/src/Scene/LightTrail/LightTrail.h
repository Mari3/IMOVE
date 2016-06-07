//
// Created by Wouter Posdijk on 12/05/16.
//

#ifndef IMOVE_LIGHTTRAIL_H
#define IMOVE_LIGHTTRAIL_H


#include "../../Util/Vector2.h"
#include "../Util/Timer.h"

class LightTrail {
private:
    Vector2 prevLocation, prevPrevLocation, speed;
    Timer lifespan;
    bool hasLifespan;
public:
    Vector2 location;
    float hue;
    LightTrail(Vector2 location, Vector2 speed, float hue, float lifespan = -1);
    void applyForce(Vector2 force, float dt, float speedCap, bool sidesEnabled, unsigned int screenWidth = 0, unsigned int screenHeight = 0);
    bool tick(float dt);
    Vector2 getLocation();
    float getAngle();
    Vector2 getSize();
    Vector2 getSpeed();
};


#endif //IMOVE_LIGHTTRAIL_H
