//
// Created by Wouter Posdijk on 02/06/16.
//

#ifndef IMOVE_NOPEOPLECONDITION_H
#define IMOVE_NOPEOPLECONDITION_H


#include "../Configuration/LightTrailSceneConfiguration.h"
#include "../Repositories/LightsSceneRepositories.h"
#include "../../Condition.h"

class NoPeopleCondition : public Condition {
private:
    int prevSize = -1;
    LightPersonRepository *lightPeople;
    GravityPointRepository *gravityPoints;
    LightTrailSceneConfiguration config;
    LightTrailRepository *lightTrails;
public:
    int check(float dt, std::vector<Action *> &actions) override;
    NoPeopleCondition(
    	LightPersonRepository *lightPeople,
    	GravityPointRepository *gravityPoints,
        const LightTrailSceneConfiguration &config,
        LightTrailRepository *lightTrails
    );
};


#endif //IMOVE_NOPEOPLECONDITION_H
