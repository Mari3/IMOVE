#include "Scene.h"

Scene::Scene() {
    //Initialize vectors
    actions = std::vector<std::unique_ptr<Action>>();
    conditions = std::vector<std::unique_ptr<Condition>>();
}


// Executes conditions and actions, that are to be added in the constructor of a subclass.
void Scene::update(float dt) {

    processPeople();

    // Check all conditions
    for(auto &condition : conditions){
        std::vector<Action*> newActions;
        int amount = condition->check(dt,newActions);

        // Add the actions to the list
        for(int i=0;i<amount;++i){
            actions.push_back(std::unique_ptr<Action>(newActions[i]));
        }
    }

    std::vector<int> toDelete;

    // Execute the actions
    for(unsigned int i = 0; i < actions.size(); ++i) {
        // Execute the action
        actions[i]->execute(dt);

        // Remove action if it is done
        std::vector<Action*> followUp;
        if(actions[i]->isDone(followUp)){
            // If there is a followup, add it to the list
            for(auto &fu : followUp){
                actions.push_back(std::unique_ptr<Action>(fu));
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

void Scene::updatePeople(std::vector<Person> newPeople) {
    peopleQueue.push(newPeople);
}
