//
// Created by Wouter Posdijk on 30/05/16.
//

#ifndef IMOVE_REVERTMIXINGACTION_H
#define IMOVE_REVERTMIXINGACTION_H


#include "../../Action.h"
#include "../LightPerson.h"
#include "../LightTrailConfiguration.h"
#include "../Repositories/LightsSceneRepositories.h"

class RevertMixingAction : public Action {
private:
    std::shared_ptr<LightPerson> person1,person2;
    LightTrailRepository* trails;
    LightTrailConfiguration config;
    float progPerSecond, progressLeft;
public:
    RevertMixingAction(const shared_ptr<LightPerson> &person1, const shared_ptr<LightPerson> &person2,
                       float progress,
                       LightTrailRepository *trails, const LightTrailConfiguration &config);

    bool isDone(std::vector<Action*> &followUp) override;

    void execute(float dt) override;


};


#endif //IMOVE_REVERTMIXINGACTION_H
