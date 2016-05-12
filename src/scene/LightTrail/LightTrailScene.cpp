//
// Created by Wouter Posdijk on 11/05/16.
//

#include "LightTrailScene.h"
#include "Actions/UpdateLightTrailsAction.h"
#include "../Util/HueConverter.h"

void LightTrailScene::draw(sf::RenderTarget &target) {

    //TODO do drawing here
    sf::RectangleShape rect(sf::Vector2f(2560,1600));
    rect.setFillColor(sf::Color(0,0,0,3));
    target.draw(rect);

    for(auto &trail : lightTrails){
        sf::CircleShape circle(2 );
        circle.setPosition(trail->getLocation().x,trail->getLocation().y);
        circle.setFillColor(HueConverter::ToColor(trail->hue));
        target.draw(circle);
    }

    for(auto &point : gravityPoints){
        sf::CircleShape gCircle(2);
        gCircle.setFillColor(sf::Color::Red);
        gCircle.setPosition(point->location.x,point->location.y);
        target.draw(gCircle);
    }

    //sf::Mouse mouse;
    //sf::Vector2i pos = mouse.getPosition();
    //gravityPoints[0]->location.x = pos.x;
    //gravityPoints[0]->location.y = pos.y;
}

LightTrailScene::LightTrailScene() : Scene() {
    //Initialize lists
    lightSources = vector<LightSource*>();
    lightTrails = vector<LightTrail*>();

    Range hueRange(0,360);
    Range xRange(0,800);
    Range yRange(0,600);
    Range speedRange(-400,400);

    for(int i=0;i<200;++i){
        lightTrails.push_back(new LightTrail(
                Vector2(xRange.drawRandom(),yRange.drawRandom()),
                Vector2(speedRange.drawRandom(),speedRange.drawRandom()),
                hueRange.drawRandom()
        ));
    }

    gravityPoints = vector<GravityPoint*>();
    gravityPoints.push_back(new GravityPoint(Vector2(1054,800),Range(0,180,true),200000));
    gravityPoints.push_back(new GravityPoint(Vector2(1508,800),Range(181,359,true),200000));
    colorHoles = vector<ColorHole*>();

    //Add actions and conditions here
    actions.push_back(new UpdateLightTrailsAction(lightTrails,gravityPoints));
}



