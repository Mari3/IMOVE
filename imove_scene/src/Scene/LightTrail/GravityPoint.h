#ifndef IMOVE_GRAVITYPOINT_H
#define IMOVE_GRAVITYPOINT_H


#include "../Util/Range.h"
#include "../../../../scene_interface/src/Vector2.h"

using namespace scene_interface;

class GravityPoint {
private:
    bool existing = true;
public:
    Vector2 location;
    util::Range hue;
    float gravity;
    GravityPoint(Vector2 location, util::Range hue, float gravity);
};


#endif //IMOVE_GRAVITYPOINT_H
