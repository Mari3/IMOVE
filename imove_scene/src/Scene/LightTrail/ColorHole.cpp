#include "ColorHole.h"

ColorHole::ColorHole(Vector2 location, util::Range hue, float gravity, float range) : GravityPoint(location, hue, gravity, range, true)
{
    consumedTrails = std::vector<std::shared_ptr<LightTrail>>();
}

void ColorHole::consume(std::shared_ptr<LightTrail> trail) {
    consumedTrails.push_back(trail);
}

std::vector<std::shared_ptr<LightTrail>> ColorHole::explode() {
    for(auto &trail : consumedTrails){
        trail->location.x = location.x;
        trail->location.y = location.y;
    }
    return consumedTrails;
}
