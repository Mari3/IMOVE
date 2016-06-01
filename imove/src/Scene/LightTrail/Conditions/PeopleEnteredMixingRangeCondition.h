//
// Created by Wouter Posdijk on 30/05/16.
//

#ifndef IMOVE_PEOPLEENTEREDMIXINGRANGECONDITION_H
#define IMOVE_PEOPLEENTEREDMIXINGRANGECONDITION_H


#include <set>
#include "../LightTrailConfiguration.h"
#include "../Repositories/LightsSceneRepositories.h"
#include "../../Condition.h"

class PeopleEnteredMixingRangeCondition : public Condition {
private:
    LightPersonRepository* lightPeople;
    LightTrailRepository* lightTrails;
    GravityPointRepository* gravityPoints;
    LightTrailConfiguration config;
    std::set<std::pair<int,int>> withinRange;
public:
    PeopleEnteredMixingRangeCondition(LightPersonRepository* lightPeople, LightTrailRepository* lightTrails,
                                      GravityPointRepository* gravityPoints, const LightTrailConfiguration& config);
    int check(float dt, std::vector<Action *> &actions) override;

};


#endif //IMOVE_PEOPLEENTEREDMIXINGRANGECONDITION_H
