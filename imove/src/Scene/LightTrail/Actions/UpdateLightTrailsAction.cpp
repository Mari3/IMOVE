//
// Created by Wouter Posdijk on 12/05/16.
//

#include "UpdateLightTrailsAction.h"

bool UpdateLightTrailsAction::isDone(std::vector<Action*> &followUp) {
    return false;
}

void UpdateLightTrailsAction::execute(float dt) {
    lightTrails->for_each([&](std::shared_ptr<LightTrail> lightTrail){

        // Calculate the force based on the gravity points
        Vector2 force = calculateForce(*(lightTrail.get()));
        // Apply said force
        lightTrail->applyForce(force,dt,config.speedCap(),config.sidesEnabled(),config.screenWidth(),config.screenHeight());

    });
}

UpdateLightTrailsAction::UpdateLightTrailsAction(LightTrailRepository* lightTrails, GravityPointRepository* gravityPoints,
                                                 const LightTrailConfiguration& config) :
    lightTrails(lightTrails), gravityPoints(gravityPoints), config(config)
{
}

Vector2 UpdateLightTrailsAction::calculateForce(LightTrail trail) {
    Vector2 totalForce(0,0);

    gravityPoints->for_each([&](std::shared_ptr<GravityPoint> gravityPoint){

        totalForce += gravityPoint->calculateForce(trail,config);

    });
    return totalForce;
}





