//
// Created by Wouter Posdijk on 12/05/16.
//

#include "AlternatingGravityPointAction.h"
#include <memory>

bool AlternatingGravityPointAction::isDone(Action *&followUp) {
    // This action is done when a person gets close to the scene.
    if(lightPeople->size()>0) {
        gravityPoints->scheduleForRemoval(myGravityPoint);
        return true;
    }
    return false;
}

void AlternatingGravityPointAction::execute(float dt) {
    if(timer.update(dt)){ //If the timer has finished
        // Draw a new random location for the gravity point
        myGravityPoint->location.x = xRange.drawRandom();
        myGravityPoint->location.y = yRange.drawRandom();
    }
}

AlternatingGravityPointAction::AlternatingGravityPointAction(util::Range hue, util::Range xRange, util::Range yRange,
                                                             GravityPointRepository* gravityPoints,
                                                             LightPersonRepository* lightPeople,
                                                             const LightTrailConfiguration &config)
        : gravityPoints(gravityPoints), lightPeople(lightPeople),
          timer(config.gravityPointDelay(),true), xRange(xRange), yRange(yRange),
        myGravityPoint(std::shared_ptr<GravityPoint>(new GravityPoint(Vector2(0,0),hue,config.alternatingGravity())))
{
    // Register the gravity point
    gravityPoints->add(myGravityPoint);

    // Set a new random location for the gravity point
    myGravityPoint->location.x = xRange.drawRandom();
    myGravityPoint->location.y = yRange.drawRandom();
}

