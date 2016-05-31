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

        if(gravityPoint->hue.contains(trail.hue)) { // If the hue of the light trail is in the hue-range of the gravity point
            Vector2 diff = gravityPoint->location - trail.getLocation();
            float dist = diff.size();
            float proximityModifier = 1;

            if (dist < config.proximityRange()) { // If the light trail is in a certain proximity to the gravity point
                // Decrease instead of increase the gravity the closer the trail gets
                // in order to cause orbit
               // proximityModifier = config.proximityModifier() * (dist/config.proximityRange()) * (dist/config.proximityRange());
                proximityModifier = config.proximityModifier() * dist/config.proximityRange();
            }
            if(dist > 10 && (gravityPoint->range < 0 || dist < gravityPoint->range)) {
                // Add force that is inversely proportional to distance, like real gravity.
                totalForce += diff / dist / dist * proximityModifier * gravityPoint->gravity;
            }
        }

    });
    return totalForce;
}





