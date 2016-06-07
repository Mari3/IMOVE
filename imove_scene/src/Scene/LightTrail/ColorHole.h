#ifndef IMOVE_COLORHOLE_H
#define IMOVE_COLORHOLE_H

#include <vector>
#include "GravityPoint.h"
#include "LightTrail.h"
#include "../../../../scene_interface/src/Vector2.h"

using namespace scene_interface;

class ColorHole : public GravityPoint {
private:
    std::vector<LightTrail> consumedTrails;
public:
    ColorHole(Vector2 location, util::Range hue, float gravity);
    void consume(LightTrail &trail);
    std::vector<LightTrail> explode();
};


#endif //IMOVE_COLORHOLE_H
