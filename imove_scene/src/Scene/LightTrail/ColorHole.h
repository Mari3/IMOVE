#ifndef IMOVE_COLORHOLE_H
#define IMOVE_COLORHOLE_H

#include <vector>
#include <memory>
#include "GravityPoint.h"
#include "LightTrail.h"
#include "../../../../scene_interface/src/Vector2.h"

class ColorHole : public GravityPoint {
private:
    std::vector<std::shared_ptr<LightTrail>> consumedTrails;
public:
    ColorHole(Vector2 location, util::Range hue, float gravity, float range=-1);
    void consume(std::shared_ptr<LightTrail> trail);
    std::vector<std::shared_ptr<LightTrail>> explode();
};


#endif //IMOVE_COLORHOLE_H
