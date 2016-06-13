//
// Created by Wouter Posdijk on 09/06/16.
//

#ifndef IMOVE_MIXINGEFFECT_H
#define IMOVE_MIXINGEFFECT_H

#include <memory>

#include "../LightPerson.h"
#include "Effect.h"
#include "../Configuration/LightTrailConfiguration.h"

// Draws two 'progress bars' between two people,
// wherein they send their colors to each other
class MixingEffect : public Effect{
private:
    std::shared_ptr<LightPerson> person1,person2;
    float leftInCycle = 1.f, cycle = 1.f;
    sf::Color prevColor1, currentColor1, prevColor2, currentColor2, stepColor1, stepColor2;
    LightTrailConfiguration config;
public:
    MixingEffect(const std::shared_ptr<LightPerson> &person1, const std::shared_ptr<LightPerson> &person2,
                     const LightTrailConfiguration &config);

    void update(float dt) override;

    void draw(sf::RenderTarget &target) override;


};


#endif //IMOVE_MIXINGEFFECT_H
