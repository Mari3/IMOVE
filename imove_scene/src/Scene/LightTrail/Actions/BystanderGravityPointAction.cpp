#include "BystanderGravityPointAction.h"
#include "../LightTrailConfiguration.h"
#include "../../../../../scene_interface/src/Person.h"
#include "../../../../../scene_interface/src/Vector2.h"

BystanderGravityPointAction::BystanderGravityPointAction(std::shared_ptr<LightPerson> person, GravityPointRepository* gravityPoints, const LightTrailConfiguration &config)
  : gravityPoints(gravityPoints),
		person(person),
		timer(Timer(config.bystanderGravityDelay(), true)),
		config(config)
{
    gravityPoint = std::shared_ptr<GravityPoint>(new GravityPoint(Vector2(0,0),person->hue,config.bystanderGravity(),
    config.bystanderGravityRange()));
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
    }else if(x > config.screenWidth()){
        gX = config.screenWidth();
    }
    if(y < 0){
        gY = 0;
    }else if(y > config.screenHeight()){
        gY = config.screenHeight();
    }

    gravityPoint->location.x = gX;
    gravityPoint->location.y = gY;
}


bool BystanderGravityPointAction::isDone(std::vector<Action*> &followUp) {
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
