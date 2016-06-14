#include "AlternatingGravityPointAction.h"
#include "MixingAction.h"
#include <memory>

bool AlternatingGravityPointAction::isDone(std::vector<Action*> &followUp) {
    // This action is done when a person gets close to the Scene.
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

    MixingAction::shift(lightTrails,myGravityPoint->location,myGravityPoint->hue,10*dt);
}

AlternatingGravityPointAction::AlternatingGravityPointAction(
	util::Range hue,
	util::Range xRange,
    util::Range yRange,
    GravityPointRepository *gravityPoints,
    LightPersonRepository *lightPeople,
    LightTrailRepository *lightTrails,
    const LightTrailSceneConfiguration &config
) :
	xRange(xRange),
	yRange(yRange),
    gravityPoints(gravityPoints),
    lightPeople(lightPeople),
    lightTrails(lightTrails),
    timer(config.gravity().alternating().delay,true),
    myGravityPoint(std::shared_ptr<GravityPoint>(new GravityPoint(
	    Vector2(0,0),
		hue,
		config.gravity().alternating().gravity
    )))
{
    // Register the gravity point
    gravityPoints->add(myGravityPoint);

    // Set a new random location for the gravity point
    myGravityPoint->location.x = xRange.drawRandom();
    myGravityPoint->location.y = yRange.drawRandom();
}

