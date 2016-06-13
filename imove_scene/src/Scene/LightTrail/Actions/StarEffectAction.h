//
// Created by Wouter Posdijk on 12/06/16.
//

#ifndef IMOVE_STAREFFECTACTION_H
#define IMOVE_STAREFFECTACTION_H


#include "../Configuration/LightTrailConfiguration.h"
#include "../Effects/StarEffect.h"
#include "../../Action.h"

class StarEffectAction : public Action{
private:
    StarEffect effect;
public:
    StarEffectAction(const LightTrailConfiguration &config);

    bool isDone(std::vector<Action *> &followUp) override;

    void execute(float dt) override;

    void draw(sf::RenderTarget &target) override;


};


#endif //IMOVE_STAREFFECTACTION_H
