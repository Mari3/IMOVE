//
// Created by Wouter Posdijk on 12/05/16.
//

#include "UpdateLightSourcesAction.h"

UpdateLightSourcesAction::UpdateLightSourcesAction()
        :   sources(LightSourceRepository::getInstance()), trails(LightTrailRepository::getInstance()), timer(Timer(3.f,true))
{
}

bool UpdateLightSourcesAction::isDone(Action *&followUp) {
    // This action is never done
    return false;
}

void UpdateLightSourcesAction::execute(float dt) {
    if(timer.update(dt)){
        // TODO cap based on the amount of light trails

        for(auto &lightSource : *sources){
            trails->add(lightSource->sendOut());
        }
    }
}


