//
// Created by Wouter Posdijk on 30/05/16.
//

#ifndef IMOVE_MIXINGACTION_H
#define IMOVE_MIXINGACTION_H


#include "../../Action.h"
#include "../LightPerson.h"
#include "../LightTrailConfiguration.h"
#include "../Repositories/LightsSceneRepositories.h"

class MixingAction : public Action {
private:
    std::shared_ptr<LightPerson> person1, person2;
    float progress;
    LightTrailConfiguration config;
    LightTrailRepository* trails;
    void shift(shared_ptr<LightPerson> person, float amount);
public:
    MixingAction(std::shared_ptr<LightPerson> person1, std::shared_ptr<LightPerson> person2, LightTrailRepository* trails, const LightTrailConfiguration& config);
    bool isDone(Action *&followUp) override;

    void execute(float dt) override;
};


#endif //IMOVE_MIXINGACTION_H
