#ifndef IMOVE_PERSONTURNEDBYSTANDERCONDITION_H
#define IMOVE_PERSONTURNEDBYSTANDERCONDITION_H

#include <vector>
#include "../Repositories/LightPersonMapRepository.h"
#include "../../Condition.h"
#include "../Repositories/LightsSceneRepositories.h"
#include "../LightTrailConfiguration.h"
#include "../../../../../scene_interface/src/Person.h"

using namespace scene_interface;

class PersonChangedTypeCondition : public Condition {
private:
    LightPersonRepository* lightPeople;
    GravityPointRepository* gravityPoints;
    std::map<int,PersonType> oldType;
    LightTrailConfiguration config;
public:
    PersonChangedTypeCondition(LightPersonRepository* lightPeople,
                               GravityPointRepository* gravityPoints,
                                const LightTrailConfiguration& config);
    int check(float dt, std::vector<Action*> &actions) override;

public:

};


#endif //IMOVE_PERSONTURNEDBYSTANDERCONDITION_H
