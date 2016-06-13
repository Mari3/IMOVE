#include <iostream>
#include <math.h>
#include "ParticipantGravityPointAction.h"
#include "../../../../../scene_interface/src/Person.h"

ParticipantGravityPointAction::ParticipantGravityPointAction(std::shared_ptr<LightPerson> person,
                                                             GravityPointRepository* gravityPoints,
                                                             const LightTrailSceneConfiguration& config)
	: gravityPoints(gravityPoints), person(person), config(config), prevLocation(person->getLocation()),
      prevDirection(0,0), baseDirection(0,0)
{
		std::cerr << "PGPA: " << person->getLocation().x << "," << person->getLocation().y << " lb: " << person->hue.lowerBound << " ub: " << person->hue.upperBound << std::endl;

    //Create the gravity point
    gravityPoint = std::shared_ptr<GravityPoint>(new GravityPoint(
            Vector2(0,0),person->hue,config.gravity().participant().gravity,config.gravity().participant().range));

    //Create the anti gravity point
    util::Range antiHue = person->hue;
    // Set the hue to the other side of the spectrum
    antiHue += 180;
    antigravityPoint = std::shared_ptr<GravityPoint>(
            new GravityPoint(Vector2(0,0),antiHue,-config.gravity().participant().antigravity,config.gravity().participant().range)
    );

    // Register the gravity point
    gravityPoints->add(gravityPoint);
    gravityPoints->add(antigravityPoint);

    // Determine the starting direction
    float fromBottom = config.screenHeight()-person->getLocation().y;
    float fromRight = config.screenWidth()-person->getLocation().x;
    float fromLeft = person->getLocation().x;
    float fromTop = person->getLocation().y;
    if(fromBottom < fromLeft && fromBottom < fromRight && fromBottom < fromTop){
        prevDirection.y = -1;
    }else if(fromTop < fromLeft && fromTop < fromRight){
        prevDirection.y = 1;
    }else if(fromLeft < fromRight){
        prevDirection.x = 1;
    }else{
        prevDirection.x = -1;
    }
    baseDirection = prevDirection;

    // Set the location
    setLocation(0);
}

void ParticipantGravityPointAction::setLocation(float dt) {
    float px = person->getLocation().x;
    float py = person->getLocation().y;

    if(!fixed) {
        float diffThreshold = 10*dt;

        Vector2 diff = person->getLocation() - prevLocation;

        // If the difference is big enough
        if (dt > 0 && diff.size() > diffThreshold) {
            Vector2 direction = diff / diff.size();
            // If the direction differs enough
            float angle = acosf(direction.x*baseDirection.x+direction.y*baseDirection.y);
            if(angle > .2*M_PI){ // If the angle is big enough
                //fixed = true;
            }
            prevDirection = direction;
        }

        // Put the gravityPoint in front of the person
        Vector2 gPointDirection = prevDirection;
        float distThreshold = 400;
        float distToTop = py;
        float distToLeft = px;
        float distToRight = config.screenWidth()-px;
        float distToBottom = config.screenHeight()-py;
        if(distToTop < distThreshold || distToBottom < distThreshold){
            if(distToLeft < distToRight)
                gPointDirection = Vector2(1,0);
            else
                gPointDirection = Vector2(-1,0);
        }else if(distToLeft < distThreshold || distToRight < distThreshold){
            if(distToTop < distToBottom)
                gPointDirection = Vector2(0,1);
            else
                gPointDirection = Vector2(0,-1);
        }

        float x = px + config.gravity().participant().distance*gPointDirection.x;
        float y = py + config.gravity().participant().distance*gPointDirection.y;
        gravityPoint->location.x = x;
        gravityPoint->location.y = y;
        antigravityPoint->location.x = x;
        antigravityPoint->location.y = y;
    }else {
        gravityPoint->location.x = px;
        gravityPoint->location.y = py;
        antigravityPoint->location.x = px;
        antigravityPoint->location.y = py;
    }
}


bool ParticipantGravityPointAction::isDone(std::vector<Action*> &followUp) {
    // This action is done when the person it tracks is no longer a participant
    if(person->person_type != scene_interface::Person::PersonType::Participant){
        gravityPoints->scheduleForRemoval(gravityPoint);
        gravityPoints->scheduleForRemoval(antigravityPoint);
        return true;
    }
    return false;
}

void ParticipantGravityPointAction::execute(float dt) {
    setLocation(dt);

    if(person->type == StandingStill){
        gravityPoint->gravity -= config.gravity().participant().gravity/config.effect().standingStillFadeTime()*dt;
        antigravityPoint->gravity += config.gravity().participant().antigravity/config.effect().standingStillFadeTime()*dt;
        if(gravityPoint->gravity < 0)gravityPoint->gravity = 0;
        if(antigravityPoint->gravity > 0)antigravityPoint->gravity = 0;
    }else{
        gravityPoint->gravity = config.gravity().participant().gravity;
        antigravityPoint->gravity = -config.gravity().participant().antigravity;
    }

    gravityPoint->hue = person->hue;
    antigravityPoint->hue = person->hue;
    antigravityPoint->hue += 180;
}
