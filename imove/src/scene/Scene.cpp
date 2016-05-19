//
// Created by Wouter Posdijk on 11/05/16.
//

#include "Scene.h"

Scene::Scene() {
    //Initialize vectors
    actions = vector<Action*>();
    conditions = vector<Condition*>();
}

void Scene::update(float dt) {

    processPeople();

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
    vector<int> toDelete;

    for(int i=0;i<actions.size();++i){
        //Execute the action
        actions[i]->execute(dt);

        //Remove action if it is done
        Action* followUp = nullptr;
        if(actions[i]->isDone(followUp)){
            //If there is a followup, add it to the list
            if(followUp){
                actions.push_back(followUp);
            }
            toDelete.push_back(i);
        }
    }

    int modifier = 0;
    for(auto &i : toDelete){
        actions.erase(actions.begin()+i-modifier);
        modifier++;
    }
}

void Scene::updatePeople(vector<Person> newPeople) {
    peopleQueue.push(newPeople);
}







