#ifndef IMOVE_GRAVITYPOINT_H
#define IMOVE_GRAVITYPOINT_H


#include "../Util/Range.h"
#include "../../../../scene_interface/src/Vector2.h"
#include "LightTrail.h"
#include "Configuration/LightTrailSceneConfiguration.h"

class GravityPoint {
private:
    bool existing = true;
    bool colorHole;
public:
    Vector2 location;
    util::Range hue;
    float gravity, range;
    GravityPoint(Vector2 location, util::Range hue, float gravity, float range = -1, bool isColorHole=false);
    Vector2 calculateForce(LightTrail trail, const LightTrailSceneConfiguration& config);
    bool isColorHole();
};


#endif //IMOVE_GRAVITYPOINT_H
