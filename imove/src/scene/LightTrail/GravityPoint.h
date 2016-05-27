//
// Created by Wouter Posdijk on 12/05/16.
//

#ifndef IMOVE_GRAVITYPOINT_H
#define IMOVE_GRAVITYPOINT_H


#include "../Util/Range.h"
#include "../../util/Vector2.h"

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
