#ifndef IMOVE_UPDATELIGHTTRAILSACTION_H
#define IMOVE_UPDATELIGHTTRAILSACTION_H


#include "../../Action.h"
#include "../LightTrail.h"
#include "../GravityPoint.h"
#include "../Repositories/LightsSceneRepositories.h"
#include "../Configuration/LightTrailSceneConfiguration.h"
#include "../../../../../scene_interface/src/Vector2.h"

class UpdateLightTrailsAction : public Action {
private:
    LightTrailRepository* lightTrails;
    GravityPointRepository* gravityPoints;
    Vector2 calculateForce(LightTrail trail);
    const LightTrailSceneConfiguration& config;
public:
    UpdateLightTrailsAction(LightTrailRepository* lightTrails, GravityPointRepository* gravityPoints,
    const LightTrailSceneConfiguration& config);

    bool isDone(std::vector<Action*> &followUp) override;
    void execute(float dt) override;
};


#endif //IMOVE_UPDATELIGHTTRAILSACTION_H
