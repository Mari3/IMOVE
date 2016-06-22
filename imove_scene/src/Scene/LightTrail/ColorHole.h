#ifndef IMOVE_COLORHOLE_H
#define IMOVE_COLORHOLE_H

#include <vector>
#include <memory>
#include "GravityPoint.h"
#include "LightTrail.h"
#include "../../../../util/src/Vector2.h"
#include "../Util/Repository.h"

class ColorHole : public GravityPoint {
private:
    Repository<LightTrail>*  consumedTrails;
public:
    ColorHole(Vector2 location, util::Range hue, float gravity, float range=-1);
    void consume(std::shared_ptr<LightTrail> trail);
    void tickTrails(float dt);
    std::vector<std::shared_ptr<LightTrail>> explode();
};


#endif //IMOVE_COLORHOLE_H
