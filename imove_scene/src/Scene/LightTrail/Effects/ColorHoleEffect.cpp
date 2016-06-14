//
// Created by Wouter Posdijk on 09/06/16.
//

#include <math.h>
#include "ColorHoleEffect.h"
#include "../../Util/HueConverter.h"
#include "../Configuration/LightTrailSceneConfiguration.h"

void ColorHoleEffect::update(float dt) {
    int removecount = 0;
    for(auto &circle : circles){
        if(circle.color.a < 255){
            int a = static_cast<int>(200.f*dt);
            if(a+circle.color.a > 255)
                circle.color.a = 255;
            else
                circle.color.a += a;
        }
        circle.radius -= 100.f*dt;
        if(circle.radius < 0)removecount++;
    }
    for(int i=0;i<removecount;++i){
        circles.pop_front();
    }

    if(timer.update(dt)){
        addCircle();
    }
}

void ColorHoleEffect::draw(sf::RenderTarget &target) {
    for(auto &circle : circles){
        sf::CircleShape circleShape(circle.radius);
        circleShape.setFillColor(sf::Color::Transparent);
        int thickness = static_cast<int>(config.effect().colorHole().thickness*circle.radius);
        if(thickness == 0) thickness = 1;
        circleShape.setOutlineThickness(thickness);
        circleShape.setOutlineColor(circle.color);
        circleShape.setPosition(sf::Vector2f(location.x-circle.radius,location.y-circle.radius));
        target.draw(circleShape);
    }
}

void ColorHoleEffect::addCircle() {
    sf::Color color = HueConverter::ToColor(hue);
    hue += 45;
    hue = fmodf(hue,360);
    color.a = 0;
    circles.push_back(ColorCircle(color,200));
}

ColorHoleEffect::ColorHoleEffect(const Vector2 &location, const LightTrailSceneConfiguration &config)
        : timer(config.effect().colorHole().period, true), location(location), config(config) {
    addCircle();
}

void ColorHoleEffect::setLocation(const Vector2 &_location) {
    location = _location;
}





