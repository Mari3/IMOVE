//
// Created by Wouter Posdijk on 18/05/16.
//

#include "PersonChangedTypeCondition.h"
#include "../Actions/BystanderGravityPointAction.h"
#include "../Actions/ParticipantGravityPointAction.h"

int PersonChangedTypeCondition::check(float dt, vector<Action*> &actions) {
    int i = 0;
    for(auto &pair : *lightPeople){
        if((oldType.count(pair.first) == 0 || oldType[pair.first] != Bystander) && pair.second->type == Bystander){
            //Create a new action
            i++;
            actions.push_back(new BystanderGravityPointAction(pair.second));
        }
        else if((oldType.count(pair.first) == 0 || oldType[pair.first] != Participant && pair.second->type == Participant)){
            i++;
            actions.push_back(new ParticipantGravityPointAction(pair.second));
        }
        oldType[pair.first] = pair.second->type;
    }
    return i;
}

PersonChangedTypeCondition::PersonChangedTypeCondition() : lightPeople(LightPersonRepository::getInstance()) {

}

