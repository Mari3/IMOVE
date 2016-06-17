//
// Created by Wouter Posdijk on 30/05/16.
//

#ifndef IMOVE_MIXINGACTION_H
#define IMOVE_MIXINGACTION_H


#include "../../Action.h"
#include "../LightPerson.h"
#include "../Configuration/LightTrailSceneConfiguration.h"
#include "../Repositories/LightsSceneRepositories.h"
#include "../Effects/MixingEffect.h"

// Causes mixing between two participants, moving their hues closer together
class MixingAction : public Action {
private:
    std::shared_ptr<LightPerson> person1, person2;
    float progress;
    LightTrailSceneConfiguration config;
    LightTrailRepository* trails;
    GravityPointRepository* gravityPoints;
    bool mixingComplete = false;
public:
    MixingAction(std::shared_ptr<LightPerson> person1, std::shared_ptr<LightPerson> person2, LightTrailRepository* trails,
                 GravityPointRepository* gravityPoints, const LightTrailSceneConfiguration& config);
    bool isDone(std::vector<Action*> &followUp) override;

    void execute(float dt) override;


    static void shift(LightTrailRepository* trails, Vector2 location, util::Range& hue, float amount, float range);
};


#endif //IMOVE_MIXINGACTION_H
