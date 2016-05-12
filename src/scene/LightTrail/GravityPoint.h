//
// Created by Wouter Posdijk on 12/05/16.
//

#ifndef IMOVE_GRAVITYPOINT_H
#define IMOVE_GRAVITYPOINT_H


#include "../../shared/Range.h"
#include "../../shared/Vector2.h"

class GravityPoint {
private:
    Vector2 location;
    Range hue;
    float gravity;
public:
    GravityPoint(Vector2 location, Range hue, float gravity);
    const Vector2 & getLocation() const;
    const Range & getHue() const;
    float getGravity() const;
};


#endif //IMOVE_GRAVITYPOINT_H
