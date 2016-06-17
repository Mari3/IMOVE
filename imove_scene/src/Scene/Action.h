//
// Created by Wouter Posdijk on 11/05/16.
//

#ifndef IMOVE_ACTION_H
#define IMOVE_ACTION_H

#include <vector>
#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Effect.h"

//Interface
class Action {
protected:
    std::vector<std::unique_ptr<Effect>> effects;
public:
    virtual bool isDone(std::vector<Action*>& followUp) = 0;
    virtual void execute(float dt) = 0;
    void updateEffects(float dt) {
        for(auto &effect : effects){
            effect->update(dt);
        }
    }
    void draw(sf::RenderTarget &target){
        for(auto &effect : effects){
            effect->draw(target);
        }
    };
    virtual ~Action(){}
};


#endif //IMOVE_ACTION_H
