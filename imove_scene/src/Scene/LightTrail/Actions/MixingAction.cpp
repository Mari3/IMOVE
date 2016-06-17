//
// Created by Wouter Posdijk on 30/05/16.
//

#include <cmath>
#include "MixingAction.h"
#include "ExplosionAction.h"
#include "RevertMixingAction.h"

bool MixingAction::isDone(std::vector<Action*> &followUp) {
    if(mixingComplete){
        // Create explosion effects around both people
        Action* followUp1 = new ExplosionAction(person1,gravityPoints,config);
        Action* followUp2 = new ExplosionAction(person2,gravityPoints,config);
        followUp.push_back(followUp1);
        followUp.push_back(followUp2);
        return true;
    }
    float dist = (person1->getLocation()-person2->getLocation()).size();
    // If the people got too far away, or either of the people became a color hole
    // or changed type
    if(dist > config.effect().mixing().distance || person1->isColorHole ||
            person1->person_type != scene_interface::Person::PersonType::Participant ||
            person2->isColorHole
            || person2->person_type != scene_interface::Person::PersonType::Participant) {
        // Revert the mixing
        Action* revertFollowUp = new RevertMixingAction(person1,person2,progress,trails,config);
        followUp.push_back(revertFollowUp);
        return true;
    }
    return false;
}

void MixingAction::execute(float dt) {
    float dist = (person1->getLocation()-person2->getLocation()).size();
    float closeness = 1+1-dist/config.effect().mixing().distance;

    // Determine the mixing speed based on the distance between the people
    float currentProgress = closeness * config.effect().mixing().speed * dt;

    float difference = person1->hue.getCenter()-person2->hue.getCenter();
    // Determine the shifting direction
    if(difference > 180) difference -= 360;
    else if(difference < -180) difference += 360;

    if(difference > 0)
        currentProgress *= -1;

    // If the mixing would go past completion
    if(fabs(difference)/2.f < fabs(currentProgress)) {
        // Do only what is necessary to complete
        currentProgress = difference / 2.f;
        mixingComplete = true;
    }

    progress += currentProgress;

    // Shift the hues of the people closer to each other
    shift(trails, person1->getLocation(), person1->hue, currentProgress, config.effect().mixing().trailRange);
    shift(trails, person2->getLocation(), person2->hue, -currentProgress, config.effect().mixing().trailRange);

}

MixingAction::MixingAction(std::shared_ptr<LightPerson> person1, std::shared_ptr<LightPerson> person2,
                           LightTrailRepository* trails,
                           GravityPointRepository* gravityPoints,
                           const LightTrailSceneConfiguration &config) :
            person1(person1),person2(person2),config(config),trails(trails),gravityPoints(gravityPoints)
{
    progress = 0;
    effects.push_back(std::unique_ptr<Effect>(
            static_cast<Effect*>(new MixingEffect(person1, person2,
                                                  config))
    ));
}

void MixingAction::shift(LightTrailRepository* trails, Vector2 location, util::Range& hue, float amount, float range) {
    trails->for_each([&](std::shared_ptr<LightTrail> trail){
        // If the trail's hue is in the hue range
        if(hue.contains(trail->hue)) {
            float dist = (trail->getLocation() - location).size();
            // If the trail falls within the effect range
            if (dist < range) {
                // Shift the hue of the trail
                trail->hue += amount;
                trail->hue = fmodf(trail->hue,360);
            }
        }
    });
    hue += amount;
}