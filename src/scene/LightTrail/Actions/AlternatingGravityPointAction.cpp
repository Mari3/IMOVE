//
// Created by Wouter Posdijk on 12/05/16.
//

#include "AlternatingGravityPointAction.h"

bool AlternatingGravityPointAction::isDone(Action *&followUp) {
    //This action is done when a person gets close to the scene.
    if(lightPeople->size() > 0) {
        gravityPoints->scheduleForRemoval(&myGravityPoint);
        return true;
    }
    return false;
}

void AlternatingGravityPointAction::execute(float dt) {
    if(timer.update(dt)){
        myGravityPoint.location.x = xRange.drawRandom();
        myGravityPoint.location.y = yRange.drawRandom();
    }
}

AlternatingGravityPointAction::AlternatingGravityPointAction(Range hue)
        : gravityPoints(GravityPointRepository::getInstance()), lightPeople(LightPersonRepository::getInstance()),
          timer(8.f,true), xRange(0,2560), yRange(0,1600),
        myGravityPoint(Vector2(0,0),hue,300000)
{
    GravityPoint* ptr = &myGravityPoint;
    gravityPoints->add(ptr);
    myGravityPoint.location.x = xRange.drawRandom();
    myGravityPoint.location.y = yRange.drawRandom();
}
