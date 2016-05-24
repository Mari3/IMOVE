//
// Created by Wouter Posdijk on 12/05/16.
//

#ifndef IMOVE_ALTERNATINGGRAVITYPOINTACTION_H
#define IMOVE_ALTERNATINGGRAVITYPOINTACTION_H


#include "../../Action.h"
#include "../GravityPoint.h"
#include "../../../util/Timer.h"
#include "../Repositories/GravityPointVectorRepository.h"
#include "../Repositories/LightPersonMapRepository.h"
#include "../Repositories/LightsSceneRepositories.h"

class AlternatingGravityPointAction : public Action{
private:
    GravityPointRepository* gravityPoints;
    LightPersonRepository* lightPeople;
    Timer timer;
    GravityPoint myGravityPoint;
    util::Range xRange;
    util::Range yRange;
public:

    AlternatingGravityPointAction();

    bool isDone(Action *&followUp);
    void execute(float dt);
};


#endif //IMOVE_ALTERNATINGGRAVITYPOINTACTION_H
