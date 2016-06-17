//
// Created by Wouter Posdijk on 16/06/16.
//

#include "RemoveTrailsAction.h"

RemoveTrailsAction::RemoveTrailsAction(const std::shared_ptr<LightPerson> &person, LightTrailRepository *trails,
                                       const LightTrailSceneConfiguration &config)
        : person(person), trails(trails), config(config) { }

bool RemoveTrailsAction::isDone(std::vector<Action *> &followUp) {
    return true;
}

void RemoveTrailsAction::execute(float dt) {
    int removalCount = config.effect().trail().participantInitAmount-person->initiativeTrailCount;
    int i=0;
    trails->for_each([&](std::shared_ptr<LightTrail> trail){
        if(i < removalCount &&
           person->hue.contains(trail->hue) &&
           (trail->location-person->getLocation()).size() < config.effect().trail().initRange
                ){
            trails->scheduleForRemoval(trail);
            i++;
        }
    });
}