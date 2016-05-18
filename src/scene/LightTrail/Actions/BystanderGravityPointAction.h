//
// Created by Wouter Posdijk on 18/05/16.
//

#ifndef IMOVE_BYSTANDERGRAVITYPOINTACTION_H
#define IMOVE_BYSTANDERGRAVITYPOINTACTION_H


#include "../../Action.h"
#include "../Repositories/GravityPointRepository.h"
#include "../LightPerson.h"
#include "../../../shared/Timer.h"

class BystanderGravityPointAction : public Action {
private:
    GravityPointRepository* gravityPoints;
    GravityPoint* gravityPoint;
    LightPerson* person;
    Timer timer;
    bool gravityPointActive;
    void setLocation();
public:
    BystanderGravityPointAction(LightPerson* person);

    bool isDone(Action *&followUp) override;

    void execute(float dt) override;


};


#endif //IMOVE_BYSTANDERGRAVITYPOINTACTION_H
