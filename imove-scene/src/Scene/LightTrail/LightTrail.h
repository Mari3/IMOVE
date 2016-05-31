//
// Created by Wouter Posdijk on 12/05/16.
//

#ifndef IMOVE_LIGHTTRAIL_H
#define IMOVE_LIGHTTRAIL_H


#include "../../Util/Vector2.h"

class LightTrail {
private:
    Vector2 location, speed;
public:
    float hue;
    LightTrail(Vector2 location, Vector2 speed, float hue);
    void applyForce(Vector2 force, float dt, float speedCap, bool sidesEnabled, unsigned int screenWidth = 0, unsigned int screenHeight = 0);
    Vector2 getLocation();
    Vector2 getSpeed();
};


#endif //IMOVE_LIGHTTRAIL_H
