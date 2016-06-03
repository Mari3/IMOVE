#ifndef IMOVE_LIGHTTRAIL_H
#define IMOVE_LIGHTTRAIL_H

#include "../../../../scene_interface/src/Vector2.h"

class LightTrail {
private:
    scene_interface::Vector2 location, speed;
public:
    float hue;
    LightTrail(scene_interface::Vector2 location, scene_interface::Vector2 speed, float hue);
    void applyForce(scene_interface::Vector2 force, float dt, float speedCap, bool sidesEnabled, unsigned int screenWidth = 0, unsigned int screenHeight = 0);
    scene_interface::Vector2 getLocation();
    scene_interface::Vector2 getSpeed();
};


#endif //IMOVE_LIGHTTRAIL_H
