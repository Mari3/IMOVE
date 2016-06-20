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

    std::vector<std::shared_ptr<LightTrail>> hueTrails;

    trails->for_each([&](std::shared_ptr<LightTrail> trail){
        hueTrails.push_back(trail);
    });

    Vector2 ploc = person->getLocation();
    std::sort(hueTrails.begin(),hueTrails.end(),[ploc](std::shared_ptr<LightTrail> x, std::shared_ptr<LightTrail> y){
        return (x->location-ploc).size() < (y->location-ploc).size();
    });

    for(int i=0;i<removalCount&&i<hueTrails.size();++i){
        trails->scheduleForRemoval(hueTrails[i]);
    }
}