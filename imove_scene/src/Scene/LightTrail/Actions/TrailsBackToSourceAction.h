//
// Created by Wouter Posdijk on 02/06/16.
//

#ifndef IMOVE_TRAILSBACKTOSOURCEACTION_H
#define IMOVE_TRAILSBACKTOSOURCEACTION_H


#include "../../Action.h"
#include "../Repositories/LightsSceneRepositories.h"

class TrailsBackToSourceAction : public Action {

private:
    GravityPointRepository* gravityPoints;
    LightPersonRepository* lightPeople;
    shared_ptr<GravityPoint> gPoints[3];
public:
    TrailsBackToSourceAction(GravityPointRepository *gravityPoints,
                                 LightTrailConfiguration &config,
                                 LightPersonRepository *lightPeople);
    bool isDone(std::vector<Action *> &followUp) override;
    void execute(float dt) override;

};


#endif //IMOVE_TRAILSBACKTOSOURCEACTION_H
