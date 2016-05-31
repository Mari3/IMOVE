//
// Created by Wouter Posdijk on 18/05/16.
//

#ifndef IMOVE_BYSTANDERGRAVITYPOINTACTION_H
#define IMOVE_BYSTANDERGRAVITYPOINTACTION_H


#include <memory>
#include "../../Action.h"
#include "../LightPerson.h"
#include "../../Util/Timer.h"
#include "../Repositories/LightsSceneRepositories.h"
#include "../LightTrailConfiguration.h"

class BystanderGravityPointAction : public Action {
private:
    GravityPointRepository* gravityPoints;
    std::shared_ptr<GravityPoint> gravityPoint;
    std::shared_ptr<LightPerson> person;
    Timer timer;
    bool gravityPointActive;
    LightTrailConfiguration config;
    void setLocation();
public:
    explicit BystanderGravityPointAction(std::shared_ptr<LightPerson> person, GravityPointRepository* gravityPoints,
    const LightTrailConfiguration &config);

    bool isDone(std::vector<Action*> &followUp) override;

    void execute(float dt) override;


};


#endif //IMOVE_BYSTANDERGRAVITYPOINTACTION_H
