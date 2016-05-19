//
// Created by Wouter Posdijk on 12/05/16.
//

#include "AlternatingGravityPointAction.h"

bool AlternatingGravityPointAction::isDone(Action *&followUp) {
    //This action is done when a person gets close to the scene.
    gravityPoints->scheduleForRemoval(&myGravityPoint);
    return lightPeople->size()>0;
}

void AlternatingGravityPointAction::execute(float dt) {
    if(timer.update(dt)){
        myGravityPoint.location.x = xRange.drawRandom();
        myGravityPoint.location.y = yRange.drawRandom();
    }
}

AlternatingGravityPointAction::AlternatingGravityPointAction()
        : gravityPoints(GravityPointRepository::getInstance()), lightPeople(LightPersonRepository::getInstance()),
          timer(5.f,true), xRange(0,800), yRange(0,600),
        myGravityPoint(Vector2(0,0),util::Range(0,360,true),300000)
{
    GravityPoint* ptr = &myGravityPoint;
    gravityPoints->add(ptr);
    myGravityPoint.location.x = xRange.drawRandom();
    myGravityPoint.location.y = yRange.drawRandom();
}