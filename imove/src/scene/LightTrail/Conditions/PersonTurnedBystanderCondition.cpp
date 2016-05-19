//
// Created by Wouter Posdijk on 18/05/16.
//

#include "PersonTurnedBystanderCondition.h"
#include "../Actions/BystanderGravityPointAction.h"

int PersonTurnedBystanderCondition::check(float dt, Action **&actions) {
    vector<Action*> newActions;
    int i = 0;
    for(auto &pair : *lightPeople){
        if((oldType.count(pair.first) == 0 || oldType[pair.first] != Bystander) && pair.second->type == Bystander){
            //Create a new action
            i++;
            newActions.push_back(new BystanderGravityPointAction(pair.second));
        }
        oldType[pair.first] = pair.second->type;
    }
    if(i>0) {
        actions = &newActions[0];
    }
    return i;
}

PersonTurnedBystanderCondition::PersonTurnedBystanderCondition() : lightPeople(LightPersonRepository::getInstance()) {

}

