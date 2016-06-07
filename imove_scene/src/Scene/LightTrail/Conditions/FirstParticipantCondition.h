//
// Created by Wouter Posdijk on 02/06/16.
//

#ifndef IMOVE_FIRSTPARTICIPANTCONDITION_H
#define IMOVE_FIRSTPARTICIPANTCONDITION_H


#include "../../Condition.h"
#include "../Repositories/LightsSceneRepositories.h"

class FirstParticipantCondition : public Condition {

private:
    int prevSize = 0;
    LightPersonRepository *lightPeople;
    LightTrailConfiguration config;
    GravityPointRepository *gravityPoints;
public:
    FirstParticipantCondition(
    	LightPersonRepository *lightPeople,
        const LightTrailConfiguration &config,
        GravityPointRepository *gravityPoints
    );

    int check(float dt, std::vector<Action *> &actions) override;

};


#endif //IMOVE_FIRSTPARTICIPANTCONDITION_H
