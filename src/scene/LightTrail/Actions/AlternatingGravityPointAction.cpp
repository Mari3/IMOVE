//
// Created by Wouter Posdijk on 12/05/16.
//

#include "AlternatingGravityPointAction.h"

bool AlternatingGravityPointAction::isDone(Action *&followUp) {
    return false;
}

void AlternatingGravityPointAction::execute(float dt) {
    if(timer.update(dt)){
        myGravityPoint.location.x = xRange.drawRandom();
        myGravityPoint.location.y = yRange.drawRandom();
    }
}

AlternatingGravityPointAction::AlternatingGravityPointAction(vector<GravityPoint *> *gravityPoints)
        : gravityPoints(
        gravityPoints), timer(5.f,true), xRange(0,2560), yRange(0,1600),
        myGravityPoint(Vector2(0,0),Range(0,360,true),300000)
{
    GravityPoint* ptr = &myGravityPoint;
    gravityPoints->push_back(ptr);
    myGravityPoint.location.x = xRange.drawRandom();
    myGravityPoint.location.y = yRange.drawRandom();
}