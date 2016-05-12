//
// Created by Wouter Posdijk on 12/05/16.
//

#include "UpdateLightSourcesAction.h"

UpdateLightSourcesAction::UpdateLightSourcesAction(vector<LightSource*>* &sources, vector<LightTrail*>* &trails)
        :   sources(sources), trails(trails), timer(Timer(3.f,true))
{
}

bool UpdateLightSourcesAction::isDone(Action *&followUp) {
    return false;
}

void UpdateLightSourcesAction::execute(float dt) {
    if(timer.update(dt)){
        for(auto &lightSource : *sources){
            trails->push_back(lightSource->sendOut());
        }
    }
}


