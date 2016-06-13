//
// Created by Wouter Posdijk on 12/05/16.
//

#include "UpdateLightSourcesAction.h"

UpdateLightSourcesAction::UpdateLightSourcesAction(LightSourceRepository* lightSources, LightTrailRepository* lightTrails,
                                                   const LightTrailSceneConfiguration& config)
        :   sources(lightSources), trails(lightTrails), timer(Timer(config.trail().lightSource().sendOutDelay,true)),
            cap(static_cast<unsigned int>(config.trail().lightSource().trailCap))
{
}

bool UpdateLightSourcesAction::isDone(std::vector<Action*> &followUp) {
    // This action is never done
    return false;
}

void UpdateLightSourcesAction::execute(float dt) {
    if(trails->size() < cap && timer.update(dt)){ // If the timer is complete and there aren't too many trails yet
        sources->for_each([&](std::shared_ptr<LightSource> lightSource){

            // Send out a trail and add it to the light trail repository
            trails->add(std::shared_ptr<LightTrail>(lightSource->sendOut()));

        });
    }
}


