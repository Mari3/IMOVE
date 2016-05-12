//
// Created by Wouter Posdijk on 12/05/16.
//

#ifndef IMOVE_LIGHTTRAIL_H
#define IMOVE_LIGHTTRAIL_H


#include "../../shared/Vector2.h"

class LightTrail {
private:
    Vector2 location, speed;
public:
    LightTrail(Vector2 location, Vector2 speed, float hue);
    void update(Vector2 force, float dt);
    Vector2 getLocation();
    float hue;
};


#endif //IMOVE_LIGHTTRAIL_H
