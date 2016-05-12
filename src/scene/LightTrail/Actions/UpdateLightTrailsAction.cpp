//
// Created by Wouter Posdijk on 12/05/16.
//

#include "UpdateLightTrailsAction.h"

#define FORCE_CONSTANT 1
#define PROXIMITY_CONSTANT 200
#define PROXIMITY_MODIFIER 0

bool UpdateLightTrailsAction::isDone(Action *&followUp) {
    return false;
}

void UpdateLightTrailsAction::execute(float dt) {
    for(auto &lightTrail : *lightTrails){
        Vector2 force = calculateForce(*lightTrail);
        lightTrail->update(force,dt);
    }
}

UpdateLightTrailsAction::UpdateLightTrailsAction(vector<LightTrail*>* &lightTrails,
                                                 vector<GravityPoint*>* &gravityPoints) :
    lightTrails(lightTrails), gravityPoints(gravityPoints)
{
}

Vector2 UpdateLightTrailsAction::calculateForce(LightTrail trail) {
    Vector2 totalForce(0,0);
    //Range slowDownRange(20,160);

    for(auto &gravityPoint : *gravityPoints){
        if(gravityPoint->hue.contains(trail.hue)) {
            Vector2 diff = gravityPoint->location - trail.getLocation();
            float dist = diff.size();
            float proximityModifier = 1;
            if (dist < PROXIMITY_CONSTANT) {
                //float angle = diff.angle(trail.getSpeed());
                //if (slowDownRange.contains(angle))
                    proximityModifier = PROXIMITY_MODIFIER;
            }
            totalForce += diff / dist / dist * FORCE_CONSTANT * proximityModifier * gravityPoint->gravity;
        }
    }
    return totalForce;
}



