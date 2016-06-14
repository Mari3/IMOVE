//
// Created by Wouter Posdijk on 02/06/16.
//

#include "FirstParticipantCondition.h"
#include "../Actions/TrailsBackToSourceAction.h"

int FirstParticipantCondition::check(float dt, std::vector<Action *> &actions) {
    int i=0;
    int size = 0;
    lightPeople->for_each([&](std::shared_ptr<LightPerson> person){
        if(person->person_type == scene_interface::Person::PersonType::Participant)
            size++;
    });

    if(size == 1 && prevSize == 0){
        Action* newAction = new TrailsBackToSourceAction(gravityPoints,config,lightPeople);
        actions.push_back(newAction);
        i++;
    }

    prevSize = size;
    return i;
}

FirstParticipantCondition::FirstParticipantCondition(LightPersonRepository *lightPeople,
                                                     const LightTrailConfiguration &config,
                                                     GravityPointRepository *gravityPoints)
        : lightPeople(
        lightPeople), config(config), gravityPoints(gravityPoints) { }
