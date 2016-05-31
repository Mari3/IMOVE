//
// Created by Wouter Posdijk on 12/05/16.
//

#ifndef IMOVE_GRAVITYPOINT_H
#define IMOVE_GRAVITYPOINT_H


#include "../Util/Range.h"
#include "../../Util/Vector2.h"
#include "LightTrail.h"
#include "LightTrailConfiguration.h"

class GravityPoint {
private:
    bool existing = true;
public:
    Vector2 location;
    util::Range hue;
    float gravity, range;
    GravityPoint(Vector2 location, util::Range hue, float gravity, float range = -1);
    Vector2 calculateForce(LightTrail trail, const LightTrailConfiguration& config);
};


#endif //IMOVE_GRAVITYPOINT_H
