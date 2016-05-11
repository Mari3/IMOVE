//
// Created by Wouter Posdijk on 11/05/16.
//

#include "Scene.h"

void Scene::updatePeople(vector <Person> people) {
    this->people = people;
}

void Scene::update(float dt) {

    //Check all conditions
    for(auto &condition : conditions){
        Action** newActions;
        int amount = condition->check(dt,newActions);

        //Add the actions to the list
        for(int i=0;i<amount;++i){
            actions.push_back(newActions[i]);
        }
    }

    //Execute the actions
    for(int i=0;i<actions.size();++i){
        //Execute the action
        actions[i]->execute(dt);

        //Remove action if it is done
        Action* followUp;
        if(actions[i]->isDone(followUp)){
            //If there is a followup, add it to the list
            if(followUp != NULL){
                actions.push_back(followUp);
            }
            actions.erase(actions.begin()+i);
            --i;
        }
    }
}



