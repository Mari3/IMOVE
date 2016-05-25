//
// Created by Wouter Posdijk on 18/05/16.
//

#ifndef IMOVE_BYSTANDERGRAVITYPOINTACTION_H
#define IMOVE_BYSTANDERGRAVITYPOINTACTION_H


#include "../../Action.h"
#include "../Repositories/GravityPointVectorRepository.h"
#include "../LightPerson.h"
#include "../../../util/Timer.h"
#include "../Repositories/LightsSceneRepositories.h"
#include "../LightTrailConfiguration.h"

class BystanderGravityPointAction : public Action {
private:
    GravityPointRepository* gravityPoints;
    std::shared_ptr<GravityPoint> gravityPoint;
    std::shared_ptr<LightPerson> person;
    Timer timer;
    bool gravityPointActive;
    void setLocation();
public:
    explicit BystanderGravityPointAction(std::shared_ptr<LightPerson> person, GravityPointRepository* gravityPoints,
    LightTrailConfiguration config);

    bool isDone(Action *&followUp) override;

    void execute(float dt) override;


};


#endif //IMOVE_BYSTANDERGRAVITYPOINTACTION_H
