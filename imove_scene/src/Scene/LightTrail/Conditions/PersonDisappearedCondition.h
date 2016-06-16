//
// Created by Wouter Posdijk on 16/06/16.
//

#ifndef IMOVE_PERSONDISAPPEAREDCONDITION_H
#define IMOVE_PERSONDISAPPEAREDCONDITION_H


#include "../Repositories/LightsSceneRepositories.h"
#include "../../Condition.h"

class PersonDisappearedCondition : public Condition {
private:
    LightPersonRepository* lightPeople;
    LightTrailRepository* trails;
    LightTrailSceneConfiguration config;
public:
    PersonDisappearedCondition(LightPersonRepository *lightPeople, LightTrailRepository *trails,
                               const LightTrailSceneConfiguration &config);

    int check(float dt, std::vector<Action *> &actions) override;


};


#endif //IMOVE_PERSONDISAPPEAREDCONDITION_H
