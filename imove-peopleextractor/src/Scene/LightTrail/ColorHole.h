//
// Created by Wouter Posdijk on 12/05/16.
//

#ifndef IMOVE_COLORHOLE_H
#define IMOVE_COLORHOLE_H


#include <vector>
#include "GravityPoint.h"
#include "LightTrail.h"

class ColorHole : public GravityPoint {
private:
    std::vector<LightTrail> consumedTrails;
public:
    ColorHole(Vector2 location, util::Range hue, float gravity);
    void consume(LightTrail &trail);
    std::vector<LightTrail> explode();
};


#endif //IMOVE_COLORHOLE_H
