//
// Created by Wouter Posdijk on 18/05/16.
//

#include "PersonChangedTypeCondition.h"
#include "../Actions/BystanderGravityPointAction.h"
#include "../Actions/ParticipantGravityPointAction.h"

int PersonChangedTypeCondition::check(float dt, vector<Action*> &actions) {
    int i = 0;
    for(auto &person : *lightPeople){
        // If the person turned bystander
        if((oldType.count(person->getId()) == 0 || oldType[person->getId()] != Bystander) && person->type == Bystander){
            // Create a new bystander action
            i++;
            actions.push_back(new BystanderGravityPointAction(person));
        } // Else if the person turned particpant
        else if((oldType.count(person->getId()) == 0 || oldType[person->getId()] != Participant && person->type == Participant))
        {
            // Create a new participant action
            i++;
            actions.push_back(new ParticipantGravityPointAction(person));
        }
        oldType[person->getId()] = person->type;
    }
    return i;
}

PersonChangedTypeCondition::PersonChangedTypeCondition() : lightPeople(LightPersonMapRepository::getInstance()) {

}

