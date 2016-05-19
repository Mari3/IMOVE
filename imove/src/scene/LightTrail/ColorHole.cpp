//
// Created by Wouter Posdijk on 12/05/16.
//

#include "ColorHole.h"

ColorHole::ColorHole(Vector2 location, Range hue, float gravity) : GravityPoint(location, hue, gravity)
{
    consumedTrails = vector<LightTrail>();
}

void ColorHole::consume(LightTrail &trail) {
    consumedTrails.push_back(trail);
}

vector<LightTrail> ColorHole::explode() {
    destroy();
    return consumedTrails;
}



