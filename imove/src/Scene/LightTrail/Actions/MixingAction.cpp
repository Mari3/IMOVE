//
// Created by Wouter Posdijk on 30/05/16.
//

#include <cmath>
#include "MixingAction.h"
#include "ExplosionAction.h"
#include "RevertMixingAction.h"

bool MixingAction::isDone(std::vector<Action*> &followUp) {
    if(mixingComplete){
        Action* followUp1 = new ExplosionAction(person1,gravityPoints,config);
        Action* followUp2 = new ExplosionAction(person2,gravityPoints,config);
        followUp.push_back(followUp1);
        followUp.push_back(followUp2);
        return true;
    }
    float dist = (person1->getLocation()-person2->getLocation()).size();
    if(dist > config.mixingDistance()) {
        Action* revertFollowUp = new RevertMixingAction(person1,person2,progress,trails,config);
        followUp.push_back(revertFollowUp);
        return true;
    }
    return false;
}

void MixingAction::execute(float dt) {
    float dist = (person1->getLocation()-person2->getLocation()).size();
    float closeness = 1+1-dist/config.mixingDistance();
    float currentProgress = closeness * config.mixingSpeed() * dt;

    float difference = person1->hue.getCenter()-person2->hue.getCenter();
    if(difference > 180) difference -= 360;
    else if(difference < -180) difference += 360;

    if(difference > 0)
        currentProgress *= -1;

    if(fabs(difference)/2.f < fabs(currentProgress)) {
        currentProgress = difference / 2.f;
        mixingComplete = true;
    }

    progress += currentProgress;

    shift(trails, person1, currentProgress);
    shift(trails, person2, -currentProgress);

}

MixingAction::MixingAction(std::shared_ptr<LightPerson> person1, std::shared_ptr<LightPerson> person2,
                           LightTrailRepository* trails,
                           GravityPointRepository* gravityPoints,
                           const LightTrailConfiguration &config) :
            person1(person1),person2(person2),trails(trails),gravityPoints(gravityPoints),config(config)
{
    progress = 0;
}

void MixingAction::shift(LightTrailRepository* trails, std::shared_ptr<LightPerson> person, float amount) {
    trails->for_each([&](std::shared_ptr<LightTrail> trail){
        if(person->hue.contains(trail->hue)) {
            float dist = (trail->getLocation() - person->getLocation()).size();
            if (dist < 400) {
                trail->hue += amount;
            }
        }
    });
    person->hue += amount;
}



