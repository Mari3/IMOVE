//
// Created by Wouter Posdijk on 12/06/16.
//

#include "StarEffect.h"

StarEffect::StarEffect(const LightTrailSceneConfiguration &config) : config(config) {
    util::Range xRange(0,config.screenWidth());
    util::Range yRange(0,config.screenHeight());
    util::Range speedRange(-config.effect().star().speed,config.effect().star().speed);

    for(int i=0;i<config.effect().star().amount;++i){
        float speed = speedRange.drawRandom();
        Vector2 loc(xRange.drawRandom(),yRange.drawRandom());
        int size = rand()%4+1;
        stars.push_back(Star(loc,speed,size));
    }
}

void StarEffect::update(float dt) {
    for(auto &star : stars){
        star.location.x += star.speed;
        if(star.speed > 0 && star.location.x > config.screenWidth())
            star.location.x = 0;
        else if(star.speed < 0 && star.location.x < 0)
            star.location.x = config.screenWidth();
    }
}

void StarEffect::draw(sf::RenderTarget &target) {
    for(auto &star : stars){
        sf::RectangleShape rect(sf::Vector2f(star.size,star.size));
        rect.setFillColor(sf::Color::Black);
        rect.setPosition(star.location.x,star.location.y);
        target.draw(rect);
    }
}