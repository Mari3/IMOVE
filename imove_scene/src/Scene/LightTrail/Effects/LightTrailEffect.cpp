//
// Created by Wouter Posdijk on 10/06/16.
//

#include "LightTrailEffect.h"
#include "../../Util/HueConverter.h"

LightTrailEffect::LightTrailEffect(LightTrailRepository *trails, const LightTrailSceneConfiguration &config,
                                   sf::RenderTexture &texture) :
        trails(trails),
        config(config), texture(texture) {
}

void LightTrailEffect::update(float dt) {
    // Do nothing
}

void LightTrailEffect::draw(sf::RenderTarget &target) {

    trails->for_each([&](std::shared_ptr<LightTrail> trail){
        Vector2 size = trail->getSize()*config.trail().trail().thickness;

        sf::RectangleShape circle(sf::Vector2f(size.x, size.y) );
        circle.setRotation(trail->getAngle());
        circle.setPosition(trail->getLocation().x,trail->getLocation().y);
        circle.setFillColor(HueConverter::ToColor(trail->hue));
        texture.draw(circle);
    });
}