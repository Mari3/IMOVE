//
// Created by Wouter Posdijk on 12/05/16.
//

#ifndef IMOVE_COLORHOLE_H
#define IMOVE_COLORHOLE_H


#include <vector>
#include "GravityPoint.h"
#include "LightTrail.h"

using namespace std;

class ColorHole : public GravityPoint {
private:
    vector<LightTrail> consumedTrails;
public:
    ColorHole(Vector2 location, Range hue, float gravity);
    void consume(LightTrail &trail);
    vector<LightTrail> explode();
};


#endif //IMOVE_COLORHOLE_H
