//
// Created by Wouter Posdijk on 11/05/16.
//

#include "LightTrailScene.h"
#include "Actions/UpdateLightTrailsAction.h"
#include "../Util/HueConverter.h"
#include "Actions/UpdateLightSourcesAction.h"
#include "Actions/AlternatingGravityPointAction.h"

void LightTrailScene::draw(sf::RenderTarget &target) {

    //TODO do drawing here
    sf::RectangleShape rect(sf::Vector2f(2560,1600));
    rect.setFillColor(sf::Color(0,0,0,3));
    target.draw(rect);

    for(auto &trail : lightTrails){
        sf::RectangleShape circle(sf::Vector2f(3,3) );
        circle.setPosition(trail->getLocation().x,trail->getLocation().y);
        circle.setFillColor(HueConverter::ToColor(trail->hue));
        target.draw(circle);
    }

    for(auto &point : gravityPoints){
        sf::CircleShape gCircle(8);
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
    lightSources.push_back(new LightSource(Vector2(0,0),Range(0,90,true),Range(0,90,true),Range(0,400)));
    lightSources.push_back(new LightSource(Vector2(2560,0),Range(90,180,true),Range(90,180,true),Range(0,400)));
    lightSources.push_back(new LightSource(Vector2(0,1600),Range(180,270,true),Range(270,0,true),Range(0,400)));
    lightSources.push_back(new LightSource(Vector2(2560,1600),Range(270,360,true),Range(180,270,true),Range(0,400)));

    lightTrails = vector<LightTrail*>();

    /*Range hueRange(0,360);
    Range xRange(0,800);
    Range yRange(0,600);
    Range speedRange(-400,400);

    for(int i=0;i<200;++i){
        lightTrails.push_back(new LightTrail(
                Vector2(xRange.drawRandom(),yRange.drawRandom()),
                Vector2(speedRange.drawRandom(),speedRange.drawRandom()),
                hueRange.drawRandom()
        ));
    }*/

    gravityPoints = vector<GravityPoint*>();
    //gravityPoints.push_back(new GravityPoint(Vector2(1054,800),Range(0,180,true),200000));
    //gravityPoints.push_back(new GravityPoint(Vector2(1508,800),Range(181,359,true),200000));
    colorHoles = vector<ColorHole*>();

    //Add actions and conditions here
    vector<LightTrail*>* lightTrailsPtr = &lightTrails;
    vector<LightSource*>* lightSourcesPtr = &lightSources;
    vector<GravityPoint*>* gravityPointsPtr = &gravityPoints;

    actions.push_back(new UpdateLightTrailsAction(lightTrailsPtr,gravityPointsPtr));
    actions.push_back(new UpdateLightSourcesAction(lightSourcesPtr,lightTrailsPtr));
    actions.push_back(new AlternatingGravityPointAction(gravityPointsPtr));
    actions.push_back(new AlternatingGravityPointAction(gravityPointsPtr));
}



