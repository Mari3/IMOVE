//
// Created by Wouter Posdijk on 19/05/16.
//

#include "ParticipantGravityPointAction.h"

ParticipantGravityPointAction::ParticipantGravityPointAction(std::shared_ptr<LightPerson> person, GravityPointRepository* gravityPoints,
                                                             const LightTrailConfiguration& config) : person(person),
                                                                                gravityPoints(gravityPoints)
{
    gravityPoint = std::shared_ptr<GravityPoint>(new GravityPoint(Vector2(0,0),person->hue,config.participantGravity()));
    setLocation();
    // Register the gravity point
    gravityPoints->add(gravityPoint);
}

void ParticipantGravityPointAction::setLocation() {
    gravityPoint->location.x = person->getLocation().x;
    gravityPoint->location.y = person->getLocation().y;
}


bool ParticipantGravityPointAction::isDone(Action *&followUp) {
    // This action is done when the person it tracks is no longer a participant
    if(person->type != Participant){
        gravityPoints->scheduleForRemoval(gravityPoint);
        return true;
    }
    return false;
}

void ParticipantGravityPointAction::execute(float dt) {
    setLocation();
}