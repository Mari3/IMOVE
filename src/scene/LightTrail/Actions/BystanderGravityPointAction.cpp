//
// Created by Wouter Posdijk on 18/05/16.
//

#include "BystanderGravityPointAction.h"

#define WIDTH 2560
#define HEIGHT 1600

BystanderGravityPointAction::BystanderGravityPointAction(LightPerson* person) : person(person),
    gravityPoints(GravityPointRepository::getInstance())
{
    gravityPoint = new GravityPoint(Vector2(0,0),person->hue,300000);
    setLocation();
    gravityPoints->add(gravityPoint);
}

void BystanderGravityPointAction::setLocation() {
    float x = person->getLocation().x;
    float y = person->getLocation().y;
    float gX = x;
    float gY = y;
    if(x < 200){
        gX = 200;
    }else if(x > WIDTH-200){
        gX = WIDTH-200;
    }
    if(y < 200){
        gY = 200;
    }else if(y > HEIGHT-200){
        gY = HEIGHT-200;
    }
    gravityPoint->location.x = gX;
    gravityPoint->location.y = gY;
}


bool BystanderGravityPointAction::isDone(Action *&followUp) {
    if(person->type != Bystander){
        gravityPoints->scheduleForRemoval(gravityPoint);
        return true;
    }
    return false;
}

void BystanderGravityPointAction::execute(float dt) {
    setLocation();
}