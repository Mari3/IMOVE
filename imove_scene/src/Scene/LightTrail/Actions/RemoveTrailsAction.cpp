//
// Created by Wouter Posdijk on 16/06/16.
//

#include <iostream>
#include "RemoveTrailsAction.h"

RemoveTrailsAction::RemoveTrailsAction(const std::shared_ptr<LightPerson> &person, LightTrailRepository *trails,
                                       const LightTrailSceneConfiguration &config)
        : person(person), trails(trails), config(config) { }

bool RemoveTrailsAction::isDone(std::vector<Action *> &followUp) {
    return true;
}

void RemoveTrailsAction::execute(float dt) {

}
