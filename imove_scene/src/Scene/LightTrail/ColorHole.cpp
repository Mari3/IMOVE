#include "ColorHole.h"

ColorHole::ColorHole(Vector2 location, util::Range hue, float gravity) : GravityPoint(location, hue, gravity)
{
    consumedTrails = std::vector<LightTrail>();
}

void ColorHole::consume(LightTrail &trail) {
    consumedTrails.push_back(trail);
}

std::vector<LightTrail> ColorHole::explode() {
    return consumedTrails;
}
