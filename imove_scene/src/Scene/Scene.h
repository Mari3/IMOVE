#ifndef IMOVE_SCENE_H
#define IMOVE_SCENE_H

#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>
#include <memory>
#include "../../../scene_interface/src/People.h"
#include "Action.h"
#include "Condition.h"

class Scene {
protected:
    std::queue<scene_interface::People> peopleQueue;
    std::vector<std::unique_ptr<Action>> actions; //Vector of pointers for polymorphism
    std::vector<std::unique_ptr<Condition>> conditions; //Idem
    virtual void processPeople() = 0;
public:
    Scene();
    void updatePeople(scene_interface::People newPeople);
    void update(float dt);
    virtual void draw(sf::RenderTarget &target) = 0;
};


#endif //IMOVE_SCENE_H
