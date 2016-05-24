//
// Created by Wouter Posdijk on 18/05/16.
//

#include "BystanderGravityPointAction.h"

#define WIDTH 800
#define HEIGHT 600

BystanderGravityPointAction::BystanderGravityPointAction(LightPerson* person) : person(person),
    gravityPoints(GravityPointVectorRepository::getInstance()), timer(Timer(5,true))
{
    gravityPoint = new GravityPoint(Vector2(0,0),person->hue,300000);
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