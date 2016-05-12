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

    for(auto &point : gravityPoints){
        sf::CircleShape gCircle(2);
        gCircle.setFillColor(sf::Color::Red);
        gCircle.setPosition(point->location.x,point->location.y);
        target.draw(gCircle);
    }
}

LightTrailScene::LightTrailScene() : Scene() {
    //Initialize lists
    lightSources = vector<LightSource*>();
    lightTrails = vector<LightTrail*>();
    lightTrails.push_back(new LightTrail(Vector2(200,200),Vector2(100,0),0));
    gravityPoints = vector<GravityPoint*>();
    gravityPoints.push_back(new GravityPoint(Vector2(200,100),Range(.9,.1,true),11000));
    colorHoles = vector<ColorHole*>();

    //Add actions and conditions here
    actions.push_back(new UpdateLightTrailsAction(lightTrails,gravityPoints));
}



