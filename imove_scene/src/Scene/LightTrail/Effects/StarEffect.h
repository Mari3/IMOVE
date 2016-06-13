//
// Created by Wouter Posdijk on 12/06/16.
//

#ifndef IMOVE_STAREFFECT_H
#define IMOVE_STAREFFECT_H


#include "Effect.h"
#include "../../../../../scene_interface/src/Vector2.h"
#include "../Configuration/LightTrailConfiguration.h"

using namespace scene_interface;

struct Star {
    Vector2 location;
    float speed;
    int size;
    Star(Vector2 location, float speed, int size) : location(location), speed(speed), size(size) {}
};

// Draws horizontally moving 'stars' on the scene
class StarEffect : public Effect {
private:
    std::vector<Star> stars;
    LightTrailConfiguration config;
public:
    StarEffect(const LightTrailConfiguration &config);

    void update(float dt) override;

    void draw(sf::RenderTarget &target) override;


};


#endif //IMOVE_STAREFFECT_H
