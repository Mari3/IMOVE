//
// Created by Wouter Posdijk on 30/05/16.
//

#include <iostream>
#include "ExplosionAction.h"

ExplosionAction::ExplosionAction(std::shared_ptr<LightPerson> person, GravityPointRepository *gravityPoints,
                                 const LightTrailConfiguration &config) :
    person(person),gravityPoints(gravityPoints),config(config),exTimer(config.explosionExTime()),inTimer(config.explosionInTime())
{
    gPoint = std::shared_ptr<GravityPoint>(new GravityPoint(person->getLocation(),person->hue,-config.explosionAntigravity()));
    gravityPoints->add(gPoint);
    std::cout << "Explosion action created!" << std::endl;
}

bool ExplosionAction::isDone(std::vector<Action*> &followUp) {
    return phase == 2;
}

void ExplosionAction::execute(float dt) {
    if(phase == 0){
        if(exTimer.update(dt)){
            phase = 1;
            gPoint->gravity = config.explosionGravity();
        }
    }else if(phase == 1){
        if(inTimer.update(dt)){
            phase = 2;
            gravityPoints->scheduleForRemoval(gPoint);
        }
    }
}