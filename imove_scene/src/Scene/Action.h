//
// Created by Wouter Posdijk on 11/05/16.
//

#ifndef IMOVE_ACTION_H
#define IMOVE_ACTION_H

#include <vector>
#include <SFML/Graphics/RenderTarget.hpp>

//Interface
class Action {
public:
    virtual bool isDone(std::vector<Action*>& followUp) = 0;
    virtual void execute(float dt) = 0;
    virtual void draw(sf::RenderTarget &target){};
    virtual ~Action(){}
};


#endif //IMOVE_ACTION_H
