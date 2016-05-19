//
// Created by Wouter Posdijk on 12/05/16.
//

#ifndef IMOVE_UPDATELIGHTTRAILSACTION_H
#define IMOVE_UPDATELIGHTTRAILSACTION_H


#include <vector>
#include "../../Action.h"
#include "../LightTrail.h"
#include "../GravityPoint.h"
#include "../Repositories/LightTrailRepository.h"
#include "../Repositories/GravityPointRepository.h"

using namespace std;

class UpdateLightTrailsAction : public Action {
private:
    LightTrailRepository* lightTrails;
    GravityPointRepository* gravityPoints;
    Vector2 calculateForce(LightTrail trail);
public:
    UpdateLightTrailsAction();

    bool isDone(Action *&followUp) override;
    void execute(float dt) override;
};


#endif //IMOVE_UPDATELIGHTTRAILSACTION_H
