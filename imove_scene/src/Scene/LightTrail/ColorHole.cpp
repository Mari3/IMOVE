#include "ColorHole.h"
#include "Repositories/LightsSceneVectorRepositories.h"

ColorHole::ColorHole(Vector2 location, util::Range hue, float gravity, float range) : GravityPoint(location, hue, gravity, range, true)
{
    consumedTrails = new LightTrailVectorRepository();
}

void ColorHole::consume(std::shared_ptr<LightTrail> trail) {
    consumedTrails->add(trail);
}

std::vector<std::shared_ptr<LightTrail>> ColorHole::explode() {
    std::vector<std::shared_ptr<LightTrail>> res;
    consumedTrails->for_each([location](std::shared_ptr<LightTrail> trail){
        trail->location.x = location.x;
        trail->location.y = location.y;
        res.push_back(trail);
    });
    return res;
}

void ColorHole::tickTrails(float dt) {
    consumedTrails->for_each([consumedTrails](std::shared_ptr<LightTrail> trail){
        if(trail->tick(dt)){
            consumedTrails->scheduleForRemoval(trail);
        }
    });
    consumedTrails->removeAll();
}


