//
// Created by Wouter Posdijk on 12/05/16.
//

#ifndef IMOVE_ALTERNATINGGRAVITYPOINTACTION_H
#define IMOVE_ALTERNATINGGRAVITYPOINTACTION_H


#include <memory>
#include "../../Action.h"
#include "../GravityPoint.h"
#include "../../Util/Timer.h"
#include "../Repositories/LightPersonMapRepository.h"
#include "../Repositories/LightsSceneRepositories.h"
#include "../LightTrailConfiguration.h"

class AlternatingGravityPointAction : public Action{
private:
    GravityPointRepository* gravityPoints;
    LightPersonRepository* lightPeople;
    LightTrailRepository* lightTrails;
    Timer timer;
    std::shared_ptr<GravityPoint> myGravityPoint;
    util::Range xRange;
    util::Range yRange;
public:

    AlternatingGravityPointAction(util::Range hue, util::Range xRange,
                                      util::Range yRange,
                                      GravityPointRepository *gravityPoints,
                                      LightPersonRepository *lightPeople,
                                      LightTrailRepository *lightTrails,
                                      const LightTrailConfiguration &config);

    bool isDone(std::vector<Action*> &followUp);
    void execute(float dt);

};


#endif //IMOVE_ALTERNATINGGRAVITYPOINTACTION_H
