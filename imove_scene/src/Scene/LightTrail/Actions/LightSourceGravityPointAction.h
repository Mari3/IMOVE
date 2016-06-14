//
// Created by Wouter Posdijk on 03/06/16.
//

#ifndef IMOVE_LIGHTSOURCEGRAVITYPOINTACTION_H
#define IMOVE_LIGHTSOURCEGRAVITYPOINTACTION_H


#include "../../Action.h"
#include "../Repositories/LightsSceneRepositories.h"

class LightSourceGravityPointAction : public Action {
private:
    LightPersonRepository* lightPeople;
    GravityPointRepository* gravityPoints;
    LightTrailSceneConfiguration config;
    std::shared_ptr<GravityPoint> gPoints[4];

public:
    LightSourceGravityPointAction(LightPersonRepository *lightPeople, GravityPointRepository *gravityPoints,
                                  const LightTrailSceneConfiguration &config);

    bool isDone(std::vector<Action *> &followUp) override;

    void execute(float dt) override;


};


#endif //IMOVE_LIGHTSOURCEGRAVITYPOINTACTION_H
