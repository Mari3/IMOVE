//
// Created by Wouter Posdijk on 12/05/16.
//

#ifndef IMOVE_UPDATELIGHTSOURCESACTION_H
#define IMOVE_UPDATELIGHTSOURCESACTION_H

#include "../../Action.h"
#include "../LightTrail.h"
#include "../LightSource.h"
#include "../../../util/Timer.h"
#include "../Repositories/LightSourceVectorRepository.h"
#include "../Repositories/LightTrailVectorRepository.h"
#include "../Repositories/LightsSceneRepositories.h"

class UpdateLightSourcesAction : public Action {
private:
    LightSourceRepository* sources;
    LightTrailVectorRepository* trails;
    Timer timer;
public:
    UpdateLightSourcesAction();
    bool isDone(Action *&followUp) override;
    void execute(float dt) override;
};


#endif //IMOVE_UPDATELIGHTSOURCESACTION_H
