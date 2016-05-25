//
// Created by Wouter Posdijk on 18/05/16.
//

#include "BystanderGravityPointAction.h"
#include "../LightTrailConfiguration.h"

#define WIDTH 800
#define HEIGHT 600

BystanderGravityPointAction::BystanderGravityPointAction(std::shared_ptr<LightPerson> person, GravityPointRepository* gravityPoints,
LightTrailConfiguration config) : person(person),
    gravityPoints(gravityPoints), timer(Timer(config.bystanderGravityDelay(),true))
{
    gravityPoint = std::shared_ptr<GravityPoint>(new GravityPoint(Vector2(0,0),person->hue,config.bystanderGravity()));
    setLocation();

    // Register the gravity point
    gravityPoints->add(gravityPoint);
    gravityPointActive = true;
}

void BystanderGravityPointAction::setLocation() {
    float x = person->getLocation().x;
    float y = person->getLocation().y;
    float gX = x;
    float gY = y;

    //Keep the x and y within the screen
    if(x < 0){
        gX = 0;
    }else if(x > WIDTH){
        gX = WIDTH;
    }
    if(y < 0){
        gY = 0;
    }else if(y > HEIGHT){
        gY = HEIGHT;
    }

    gravityPoint->location.x = gX;
    gravityPoint->location.y = gY;
}


bool BystanderGravityPointAction::isDone(Action *&followUp) {
    //This action is done when the person it tracks is not a bystander anymore
    if(person->type != Bystander){
        gravityPoints->scheduleForRemoval(gravityPoint);
        return true;
    }
    return false;
}

void BystanderGravityPointAction::execute(float dt) {
    setLocation();

    if(timer.update(dt)){ //If the timer is done
        //Switch the gravity point on or off
        if(gravityPointActive){
            gravityPoints->scheduleForRemoval(gravityPoint);
            gravityPointActive = false;
        }else{
            gravityPoints->add(gravityPoint);
            gravityPointActive = true;
        }
    }
}