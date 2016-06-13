//
// Created by Wouter Posdijk on 30/05/16.
//

#ifndef IMOVE_EXPLOSIONACTION_H
#define IMOVE_EXPLOSIONACTION_H


#include "../../Action.h"
#include "../LightPerson.h"
#include "../Repositories/LightsSceneRepositories.h"
#include "../Configuration/LightTrailConfiguration.h"
#include "../../Util/Timer.h"

// Causes an explosion around a person by temporarily
// pushing trails away and then pulling them back in
class ExplosionAction : public Action {
private:
    std::shared_ptr<LightPerson> person;
    GravityPointRepository* gravityPoints;
    LightTrailConfiguration config;
    std::shared_ptr<GravityPoint> gPoint;
    Timer exTimer,inTimer;
    int phase = 0;
public:
    ExplosionAction(std::shared_ptr<LightPerson> person, GravityPointRepository *gravityPoints, const LightTrailConfiguration& config);

    bool isDone(std::vector<Action*> &followUp) override;

    void execute(float dt) override;


};


#endif //IMOVE_EXPLOSIONACTION_H
