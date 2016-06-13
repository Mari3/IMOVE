//
// Created by Wouter Posdijk on 12/05/16.
//

#ifndef IMOVE_UPDATELIGHTSOURCESACTION_H
#define IMOVE_UPDATELIGHTSOURCESACTION_H

#include "../../Action.h"
#include "../LightTrail.h"
#include "../LightSource.h"
#include "../../Util/Timer.h"
#include "../Repositories/LightsSceneRepositories.h"
#include "../Configuration/LightTrailSceneConfiguration.h"

class UpdateLightSourcesAction : public Action {
private:
    LightSourceRepository* sources;
    LightTrailRepository* trails;
    Timer timer;
    unsigned int cap;
public:
    UpdateLightSourcesAction(LightSourceRepository* lightSources, LightTrailRepository* lightTrails,
        const LightTrailSceneConfiguration& config);
    bool isDone(std::vector<Action*> &followUp) override;
    void execute(float dt) override;
};


#endif //IMOVE_UPDATELIGHTSOURCESACTION_H
