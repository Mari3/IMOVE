//
// Created by Wouter Posdijk on 30/05/16.
//

#include <cmath>
#include "MixingAction.h"

bool MixingAction::isDone(Action *&followUp) {
    return false;
}

void MixingAction::execute(float dt) {
    float dist = (person1->getLocation()-person2->getLocation()).size();
    float closeness = 1+1-dist/512;
    float stdSpeed = 2.f;
    float currentProgress = closeness * stdSpeed * dt;

    float difference = person1->hue.getCenter()-person2->hue.getCenter();
    if(difference > 180) difference -= 360;
    else if(difference < -180) difference += 360;

    if(difference > 0)
        currentProgress *= -1;

    if(fabs(difference)/2.f < fabs(currentProgress))
        currentProgress = difference/2.f;

    shift(person1, currentProgress);
    shift(person2, -currentProgress);

}

MixingAction::MixingAction(std::shared_ptr<LightPerson> person1, std::shared_ptr<LightPerson> person2,
                           LightTrailRepository* trails,
                           const LightTrailConfiguration &config) :
            person1(person1),person2(person2),trails(trails),config(config)
{
    progress = 0;
}

void MixingAction::shift(std::shared_ptr<LightPerson> person, float amount) {
    trails->for_each([&](std::shared_ptr<LightTrail> trail){
        if(person->hue.contains(trail->hue)) {
            float dist = (trail->getLocation() - person->getLocation()).size();
            if (dist < config.proximityRange() * 1.3f) {
                trail->hue += amount;
            }
        }
    });
    person->hue += amount;
}



