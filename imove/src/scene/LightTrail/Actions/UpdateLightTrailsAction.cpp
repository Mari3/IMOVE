//
// Created by Wouter Posdijk on 12/05/16.
//

#include "UpdateLightTrailsAction.h"

#define FORCE_CONSTANT 1
#define PROXIMITY_CONSTANT 30
#define PROXIMITY_MODIFIER .5f

bool UpdateLightTrailsAction::isDone(Action *&followUp) {
    return false;
}

void UpdateLightTrailsAction::execute(float dt) {
    for(auto &lightTrail : *lightTrails){
        Vector2 force = calculateForce(*lightTrail);
        lightTrail->applyForce(force,dt);
    }
}

UpdateLightTrailsAction::UpdateLightTrailsAction(LightTrailRepository* lightTrails, GravityPointRepository* gravityPoints) :
    lightTrails(lightTrails), gravityPoints(gravityPoints)
{
}

Vector2 UpdateLightTrailsAction::calculateForce(LightTrail trail) {
    Vector2 totalForce(0,0);

    for(auto &gravityPoint : *gravityPoints){
        if(gravityPoint->hue.contains(trail.hue)) { // If the hue of the light trail is in the hue-range of the gravity point
            Vector2 diff = gravityPoint->location - trail.getLocation();
            float dist = diff.size();
            float proximityModifier = 1;

            if (dist < PROXIMITY_CONSTANT) { // If the light trail is in a certain proximity to the gravity point
                // Decrease instead of increase the gravity the closer the trail gets
                // in order to cause orbit
                proximityModifier = PROXIMITY_MODIFIER * (dist/PROXIMITY_CONSTANT) * (dist/PROXIMITY_CONSTANT);
            }
            // Add force that is inversely proportional to distance, like real gravity.
            totalForce += diff / dist / dist * FORCE_CONSTANT * proximityModifier * gravityPoint->gravity;
        }
    }
    return totalForce;
}





