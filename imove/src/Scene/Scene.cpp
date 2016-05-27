//
// Created by Wouter Posdijk on 11/05/16.
//

#include "Scene.h"

Scene::Scene() {
    //Initialize vectors
    actions = vector<std::unique_ptr<Action>>();
    conditions = vector<std::unique_ptr<Condition>>();
}


// Executes conditions and actions, that are to be added in the constructor of a subclass.
void Scene::update(float dt) {

    processPeople();

    // Check all conditions
    for(auto &condition : conditions){
        vector<Action*> newActions;
        int amount = condition->check(dt,newActions);

        // Add the actions to the list
        for(int i=0;i<amount;++i){
            actions.push_back(std::unique_ptr<Action>(newActions[i]));
        }
    }

    vector<int> toDelete;

    // Execute the actions
    for(unsigned int i = 0; i < actions.size(); ++i) {
        // Execute the action
        actions[i]->execute(dt);

        // Remove action if it is done
        Action* followUp = nullptr;
        if(actions[i]->isDone(followUp)){
            // If there is a followup, add it to the list
            if(followUp){
                actions.push_back(std::unique_ptr<Action>(followUp));
            }
            toDelete.push_back(i);
        }
    }

    // Remove done actions
    int modifier = 0;
    for(auto &i : toDelete) {
        actions.erase(actions.begin()+i-modifier);
        modifier++;
    }
}

void Scene::updatePeople(vector<Person> newPeople) {
    peopleQueue.push(newPeople);
}







