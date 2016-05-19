//
// Created by Wouter Posdijk on 19/05/16.
//

#ifndef IMOVE_PARTICIPANTGRAVITYPOINTACTION_H
#define IMOVE_PARTICIPANTGRAVITYPOINTACTION_H


#include "../Repositories/GravityPointRepository.h"
#include "../../Action.h"
#include "../LightPerson.h"

class ParticipantGravityPointAction : public Action {
private:
    GravityPointRepository* gravityPoints;
    GravityPoint* gravityPoint;
    LightPerson* person;
    void setLocation();
public:
    ParticipantGravityPointAction(LightPerson* person);

    bool isDone(Action *&followUp) override;

    void execute(float dt) override;


};


#endif //IMOVE_PARTICIPANTGRAVITYPOINTACTION_H
