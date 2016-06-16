//
// Created by Wouter Posdijk on 12/06/16.
//

#ifndef IMOVE_STAREFFECTACTION_H
#define IMOVE_STAREFFECTACTION_H


#include "../Configuration/LightTrailSceneConfiguration.h"
#include "../Effects/StarEffect.h"
#include "../../Action.h"

class StarEffectAction : public Action{
public:
    StarEffectAction(const LightTrailSceneConfiguration &config);

    bool isDone(std::vector<Action *> &followUp) override;

    void execute(float dt) override;


};


#endif //IMOVE_STAREFFECTACTION_H
