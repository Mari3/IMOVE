//
// Created by Wouter Posdijk on 12/05/16.
//

#ifndef IMOVE_UPDATELIGHTTRAILSACTION_H
#define IMOVE_UPDATELIGHTTRAILSACTION_H


#include <vector>
#include "../../Action.h"
#include "../LightTrail.h"
#include "../GravityPoint.h"

using namespace std;

class UpdateLightTrailsAction : public Action {
private:
    vector<LightTrail> lightTrails;
    vector<GravityPoint> gravityPoints;
    Vector2 calculateForce(Vector2 location);
public:
    UpdateLightTrailsAction(vector<LightTrail> &lightTrails, vector<GravityPoint> &gravityPoints);

    bool isDone(Action *&followUp) override;
    void execute(float dt) override;
};


#endif //IMOVE_UPDATELIGHTTRAILSACTION_H
