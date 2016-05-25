//
// Created by Wouter Posdijk on 12/05/16.
//

#include "UpdateLightSourcesAction.h"

UpdateLightSourcesAction::UpdateLightSourcesAction(LightSourceRepository* lightSources, LightTrailRepository* lightTrails,
                                                   const LightTrailConfiguration& config)
        :   sources(lightSources), trails(lightTrails), timer(Timer(config.sendOutDelay(),true)),
            cap(config.trailCap())
{
}

bool UpdateLightSourcesAction::isDone(Action *&followUp) {
    // This action is never done
    return false;
}

void UpdateLightSourcesAction::execute(float dt) {
    if(trails->size() < cap && timer.update(dt)){
        for(auto &lightSource : *sources){
            trails->add(shared_ptr<LightTrail>(lightSource->sendOut()));
        }
    }
}


