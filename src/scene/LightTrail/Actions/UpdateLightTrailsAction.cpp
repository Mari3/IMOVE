//
// Created by Wouter Posdijk on 12/05/16.
//

#include "UpdateLightTrailsAction.h"

#define FORCE_CONSTANT 1

bool UpdateLightTrailsAction::isDone(Action *&followUp) {
    return false;
}

void UpdateLightTrailsAction::execute(float dt) {
    for(auto &lightTrail : lightTrails){
        Vector2 force = calculateForce(lightTrail.getLocation());
        lightTrail.update(force,dt);
    }
}

UpdateLightTrailsAction::UpdateLightTrailsAction(vector<LightTrail> &lightTrails,
                                                 vector<GravityPoint> &gravityPoints) :
    lightTrails(lightTrails), gravityPoints(gravityPoints)
{
}

Vector2 UpdateLightTrailsAction::calculateForce(Vector2 location) {
    Vector2 totalForce(0,0);
    for(auto &gravityPoint : gravityPoints){
        Vector2 diff = gravityPoint.location-location;
        float dist = diff.size();
        totalForce += diff/dist/dist*FORCE_CONSTANT*gravityPoint.gravity;
    }
    return totalForce;
}



