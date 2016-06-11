#ifndef IMOVE_UPDATELIGHTTRAILSACTION_H
#define IMOVE_UPDATELIGHTTRAILSACTION_H


#include "../../Action.h"
#include "../LightTrail.h"
#include "../GravityPoint.h"
#include "../Repositories/LightsSceneRepositories.h"
#include "../LightTrailConfiguration.h"
#include "../../../../../scene_interface/src/Vector2.h"


class UpdateLightTrailsAction : public Action {
private:
    LightTrailRepository* lightTrails;
    GravityPointRepository* gravityPoints;
    Vector2 calculateForce(LightTrail trail);
    const LightTrailConfiguration& config;
public:
    UpdateLightTrailsAction(LightTrailRepository* lightTrails, GravityPointRepository* gravityPoints,
    const LightTrailConfiguration& config);

    bool isDone(Action *&followUp) override;
    void execute(float dt) override;
};


#endif //IMOVE_UPDATELIGHTTRAILSACTION_H
