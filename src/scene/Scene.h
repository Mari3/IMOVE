//
// Created by Wouter Posdijk on 11/05/16.
//

#ifndef IMOVE_SCENE_H
#define IMOVE_SCENE_H

#include <SFML/Graphics.hpp>
#include "../shared/Person.h"
#include "Action.h"
#include "Condition.h"

class Scene {
protected:
    vector<Person> people;
    vector<Action*> actions; //Vector of pointers for polymorphism
    vector<Condition*> conditions; //Idem
public:
    Scene();
    virtual void updatePeople(vector<Person> newPeople) = 0;
    void update(float dt);
    virtual void draw(sf::RenderTarget &target) = 0;
};


#endif //IMOVE_SCENE_H
