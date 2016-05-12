//
// Created by Wouter Posdijk on 11/05/16.
//

#include "LightTrailScene.h"
#include "Actions/UpdateLightTrailsAction.h"

void LightTrailScene::draw(sf::RenderTarget &target) {
    //TODO do drawing here
    sf::RectangleShape rect(sf::Vector2f(800,600));
    rect.setFillColor(sf::Color(0,0,0,1));
    target.draw(rect);

    for(auto &trail : lightTrails){
        sf::CircleShape circle(3);
        circle.setPosition(trail->getLocation().x,trail->getLocation().y);
        target.draw(circle);
    }
}

LightTrailScene::LightTrailScene() : Scene() {
    //Initialize lists
    lightSources = vector<LightSource*>();
    lightTrails = vector<LightTrail*>();
    lightTrails.push_back(new LightTrail(Vector2(0,0),Vector2(20,20),0));
    gravityPoints = vector<GravityPoint*>();
    colorHoles = vector<ColorHole*>();

    //Add actions and conditions here
    actions.push_back(new UpdateLightTrailsAction(lightTrails,gravityPoints));
}



