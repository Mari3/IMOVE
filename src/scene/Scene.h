//
// Created by Wouter Posdijk on 11/05/16.
//

#ifndef IMOVE_SCENE_H
#define IMOVE_SCENE_H

#include <SFML/Graphics.hpp>
#include "../shared/Person.h"
#include "Actions/Action.h"
#include "Conditions/Condition.h"

class Scene {
private:
    vector<Person> people;
    vector<Action*> actions;
    vector<Condition*> conditions;
public:
    void updatePeople(vector<Person> people);
    void update(float dt);
    virtual void draw(sf::RenderTarget &target) = 0;
};


#endif //IMOVE_SCENE_H
