#ifndef IMOVE_LIGHTTRAIL_H
#define IMOVE_LIGHTTRAIL_H

#include "../../../../util/src/Vector2.h"
#include "../Util/Timer.h"
#include "Configuration/LightTrailSceneConfiguration.h"

class LightTrail {
public:
    Vector2 location;
    float hue;

    LightTrail(Vector2 location, Vector2 speed, float hue, float lifespan = -1);
    void applyForce(Vector2 force, float dt, float speedCap, bool sidesEnabled, unsigned int screenWidth = 0, unsigned int screenHeight = 0);
    bool tick(float dt);
    Vector2 getLocation();
    float getAngle();
    Vector2 getSize(const LightTrailSceneConfiguration &config);
    Vector2 getSpeed();
private:
    Vector2 prevLocation, prevPrevLocation, speed;
    Timer lifespan;
    bool hasLifespan;
};


#endif //IMOVE_LIGHTTRAIL_H
