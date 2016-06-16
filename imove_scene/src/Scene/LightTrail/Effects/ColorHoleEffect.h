//
// Created by Wouter Posdijk on 09/06/16.
//

#ifndef IMOVE_COLORHOLEEFFECT_H
#define IMOVE_COLORHOLEEFFECT_H

#include <SFML/Graphics.hpp>
#include <queue>
#include "../../Effect.h"
#include "../LightPerson.h"
#include "../../Util/Timer.h"
#include "../Configuration/LightTrailSceneConfiguration.h"

struct ColorCircle {
    sf::Color color;
    float radius;
    ColorCircle(sf::Color color, float radius) : color(color), radius(radius) {}
};

// Draws circles around the person that get smaller,
// creating the effect that the person is sucking them in
class ColorHoleEffect : public Effect {
private:
    float hue = 0;
    std::deque<ColorCircle> circles;
    Timer timer;
    std::shared_ptr<LightPerson> person;
    LightTrailSceneConfiguration config;
    void addCircle();
public:
    ColorHoleEffect(const std::shared_ptr<LightPerson> &person, const LightTrailSceneConfiguration &config);
    void update(float dt) override;
    void draw(sf::RenderTarget &target) override;

};


#endif //IMOVE_COLORHOLEEFFECT_H
