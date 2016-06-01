//
// Created by Wouter Posdijk on 18/05/16.
//

#include "PersonChangedTypeCondition.h"
#include <memory>
#include "../Actions/BystanderGravityPointAction.h"
#include "../Actions/ParticipantGravityPointAction.h"

int PersonChangedTypeCondition::check(float dt, vector<Action*> &actions) {
    int i = 0;
    lightPeople->for_each([&](std::shared_ptr<LightPerson> person){
        // If the person turned bystander
        if((oldType.count(person->getId()) == 0 || oldType[person->getId()] != Bystander) && person->type == Bystander){
            // Create a new bystander action
            i++;
            actions.push_back(new BystanderGravityPointAction(person,gravityPoints,config));
        } // Else if the person turned particpant
        else if((oldType.count(person->getId()) == 0 || (oldType[person->getId()] != Participant && oldType[person->getId()] != StandingStill)) && (person->type == Participant || person->type == StandingStill))
        {
            // Create a new participant action
            i++;
            actions.push_back(new ParticipantGravityPointAction(person,gravityPoints,config));
        }
        oldType[person->getId()] = person->type;
    });
    return i;
}

PersonChangedTypeCondition::PersonChangedTypeCondition(LightPersonRepository* lightPeople,
    GravityPointRepository* gravityPoints,
    const LightTrailConfiguration& config) :
        lightPeople(lightPeople),
        gravityPoints(gravityPoints),
        config(config)
{

}

