//
// Created by Wouter Posdijk on 12/05/16.
//

#include "AlternatingGravityPointAction.h"

bool AlternatingGravityPointAction::isDone(Action *&followUp) {
    // This action is done when a person gets close to the scene.
    if(lightPeople->size()>0) {
        gravityPoints->scheduleForRemoval(&myGravityPoint);
        return true;
    }
    return false;
}

void AlternatingGravityPointAction::execute(float dt) {
    if(timer.update(dt)){ //If the timer has finished
        // Draw a new random location for the gravity point
        myGravityPoint.location.x = xRange.drawRandom();
        myGravityPoint.location.y = yRange.drawRandom();
    }
}

AlternatingGravityPointAction::AlternatingGravityPointAction()
        : gravityPoints(GravityPointRepository::getInstance()), lightPeople(LightPersonRepository::getInstance()),
          timer(5.f,true), xRange(0,800), yRange(0,600),
        myGravityPoint(Vector2(0,0),util::Range(0,360,true),300000)
{
    // Register the gravity point
    GravityPoint* ptr = &myGravityPoint;
    gravityPoints->add(ptr);

    // Set a new random location for the gravity point
    myGravityPoint.location.x = xRange.drawRandom();
    myGravityPoint.location.y = yRange.drawRandom();
}