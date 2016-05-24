//
// Created by Wouter Posdijk on 18/05/16.
//

#ifndef IMOVE_PERSONTURNEDBYSTANDERCONDITION_H
#define IMOVE_PERSONTURNEDBYSTANDERCONDITION_H


#include "../Repositories/LightPersonMapRepository.h"
#include "../../Condition.h"
#include "../Repositories/LightsSceneRepositories.h"

class PersonChangedTypeCondition : public Condition {
private:
    LightPersonRepository* lightPeople;
    GravityPointRepository* gravityPoints;
    std::map<int,PersonType> oldType;
public:
    PersonChangedTypeCondition(LightPersonRepository* lightPeople,
                               GravityPointRepository* gravityPoints);
    int check(float dt, vector<Action*> &actions) override;

public:

};


#endif //IMOVE_PERSONTURNEDBYSTANDERCONDITION_H
