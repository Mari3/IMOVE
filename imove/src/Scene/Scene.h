//
// Created by Wouter Posdijk on 11/05/16.
//

#ifndef IMOVE_SCENE_H
#define IMOVE_SCENE_H

#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>
#include <memory>
#include "../interface/Person.h"
#include "Action.h"
#include "Condition.h"

class Scene {
protected:
    queue<vector<Person>> peopleQueue;
    vector<std::unique_ptr<Action>> actions; //Vector of pointers for polymorphism
    vector<std::unique_ptr<Condition>> conditions; //Idem
    virtual void processPeople() = 0;
public:
    Scene();
    void updatePeople(vector<Person> newPeople);
    void update(float dt);
    virtual void draw(sf::RenderTarget &target) = 0;
};


#endif //IMOVE_SCENE_H
