//
// Created by Wouter Posdijk on 12/05/16.
//

#ifndef IMOVE_GRAVITYPOINT_H
#define IMOVE_GRAVITYPOINT_H


#include "../../util/Range.h"
#include "../../util/Vector2.h"

class GravityPoint {
private:
    bool existing = true;
public:
    Vector2 location;
    Range hue;
    float gravity;
    GravityPoint(Vector2 location, Range hue, float gravity);
    void destroy();
    bool exists();
};


#endif //IMOVE_GRAVITYPOINT_H
