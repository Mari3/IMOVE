#include <iostream>
#include "ParticipantGravityPointAction.h"
#include "../../../../../scene_interface/src/Person.h"
#include "../../../../../scene_interface/src/Vector2.h"

ParticipantGravityPointAction::ParticipantGravityPointAction(std::shared_ptr<LightPerson> person,
                                                             GravityPointRepository* gravityPoints,
                                                             const LightTrailConfiguration& config)
	: gravityPoints(gravityPoints), person(person), config(config) {
		std::cerr << "PGPA: " << person->getLocation().x << "," << person->getLocation().y << " lb: " << person->hue.lowerBound << " ub: " << person->hue.upperBound << std::endl; 
    gravityPoint = std::shared_ptr<GravityPoint>(new GravityPoint(
            Vector2(0,0),person->hue,config.participantGravity(),config.participantGravityRange()));

    util::Range antiHue = person->hue;
    antiHue += 180;
    antigravityPoint = std::shared_ptr<GravityPoint>(
            new GravityPoint(Vector2(0,0),antiHue,-config.participantAntigravity(),config.participantGravityRange())
    );
    // Register the gravity point
    gravityPoints->add(gravityPoint);
    gravityPoints->add(antigravityPoint);

    setLocation();
}

void ParticipantGravityPointAction::setLocation() {
    gravityPoint->location.x = person->getLocation().x;
    gravityPoint->location.y = person->getLocation().y;
    antigravityPoint->location.x = person->getLocation().x;
    antigravityPoint->location.y = person->getLocation().y;
}


bool ParticipantGravityPointAction::isDone(std::vector<Action*> &followUp) {
    // This action is done when the person it tracks is no longer a participant
    if(person->type != Participant && person->type != StandingStill){
        gravityPoints->scheduleForRemoval(gravityPoint);
        gravityPoints->scheduleForRemoval(antigravityPoint);
        return true;
    }
    return false;
}

void ParticipantGravityPointAction::execute(float dt) {
    setLocation();

    if(person->type == StandingStill){
        gravityPoint->gravity -= config.participantGravity()/40.f*dt;
        antigravityPoint->gravity += config.participantAntigravity()/40.f*dt;
        if(gravityPoint->gravity < 0)gravityPoint->gravity = 0;
        if(antigravityPoint->gravity > 0)antigravityPoint->gravity = 0;
    }else{
        gravityPoint->gravity = config.participantGravity();
        antigravityPoint->gravity = -config.participantAntigravity();
    }

    gravityPoint->hue = person->hue;
    antigravityPoint->hue = person->hue;
    antigravityPoint->hue += 180;
}
