//
// Created by Wouter Posdijk on 12/05/16.
//

#ifndef IMOVE_ALTERNATINGGRAVITYPOINTACTION_H
#define IMOVE_ALTERNATINGGRAVITYPOINTACTION_H


#include <vector>
#include "../../Action.h"
#include "../GravityPoint.h"
#include "../../../shared/Timer.h"
#include "../Repositories/GravityPointRepository.h"

using namespace std;

class AlternatingGravityPointAction : public Action{
private:
    GravityPointRepository* gravityPoints;
    Timer timer;
    GravityPoint myGravityPoint;
    Range xRange;
    Range yRange;
public:

    AlternatingGravityPointAction();

    bool isDone(Action *&followUp);
    void execute(float dt);
};


#endif //IMOVE_ALTERNATINGGRAVITYPOINTACTION_H
