#include "../../../../../imove_imp/src/Vector2.h"
#include "UpdateLightTrailsAction.h"

bool UpdateLightTrailsAction::isDone(std::vector<Action*> &followUp) {
    return false;
}

void UpdateLightTrailsAction::execute(float dt) {
    lightTrails->for_each([&](std::shared_ptr<LightTrail> lightTrail){

        // Calculate the force based on the gravity points
        Vector2 force = calculateForce(*(lightTrail.get()));
        // Apply said force
        lightTrail->applyForce(force,dt,config.trail().trail().speedCap,config.trail().sidesEnabled(),config.screenWidth(),config.screenHeight());
        if(lightTrail->tick(dt)){
            lightTrails->scheduleForRemoval(lightTrail);
        }
    });
}

UpdateLightTrailsAction::UpdateLightTrailsAction(LightTrailRepository* lightTrails, GravityPointRepository* gravityPoints,
                                                 const LightTrailSceneConfiguration& config) :
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





