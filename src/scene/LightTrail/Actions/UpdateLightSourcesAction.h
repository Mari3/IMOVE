//
// Created by Wouter Posdijk on 12/05/16.
//

#ifndef IMOVE_UPDATELIGHTSOURCESACTION_H
#define IMOVE_UPDATELIGHTSOURCESACTION_H

#include <vector>
#include "../../Action.h"
#include "../LightTrail.h"
#include "../LightSource.h"
#include "../../../shared/Timer.h"

using namespace std;

class UpdateLightSourcesAction : public Action {
private:
    vector<LightSource*>* sources;
    vector<LightTrail*>* trails;
    Timer timer;
public:
    UpdateLightSourcesAction(vector<LightSource*>* &sources, vector<LightTrail*>* &trails);
    bool isDone(Action *&followUp) override;
    void execute(float dt) override;
};


#endif //IMOVE_UPDATELIGHTSOURCESACTION_H
