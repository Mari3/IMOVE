//
// Created by Wouter Posdijk on 19/05/16.
//

#include "ParticipantGravityPointAction.h"

ParticipantGravityPointAction::ParticipantGravityPointAction(LightPerson* person) : person(person),
                                                                                gravityPoints(GravityPointVectorRepository::getInstance())
{
    gravityPoint = new GravityPoint(Vector2(0,0),person->hue,100000);
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