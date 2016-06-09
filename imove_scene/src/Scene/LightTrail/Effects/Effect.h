//
// Created by Wouter Posdijk on 09/06/16.
//

#ifndef IMOVE_EFFECT_H
#define IMOVE_EFFECT_H

#include <SFML/graphics.hpp>

class Effect {
public:
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderTarget& target) = 0;
    virtual ~Effect(){}
};


#endif //IMOVE_EFFECT_H
