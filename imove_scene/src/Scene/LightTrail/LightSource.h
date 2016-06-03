//
// Created by Wouter Posdijk on 12/05/16.
//

#ifndef IMOVE_LIGHTSOURCE_H
#define IMOVE_LIGHTSOURCE_H


#include "../../../../scene_interface/src/Vector2.h"
#include "../Util/Range.h"
#include "LightTrail.h"

class LightSource {
private:
    scene_interface::Vector2 location;
    util::Range hue,angle,speed;
public:
    LightSource(scene_interface::Vector2 location, util::Range hue, util::Range angle, util::Range speed);
    LightTrail * sendOut();
    scene_interface::Vector2 getLocation();
    util::Range getHue();
};


#endif //IMOVE_LIGHTSOURCE_H
