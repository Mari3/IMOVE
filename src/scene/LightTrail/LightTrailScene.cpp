//
// Created by Wouter Posdijk on 11/05/16.
//

#include "LightTrailScene.h"
#include "Actions/UpdateLightTrailsAction.h"
#include "../Util/HueConverter.h"
#include "Actions/UpdateLightSourcesAction.h"
#include "Actions/AlternatingGravityPointAction.h"
#include "Conditions/PersonTurnedBystanderCondition.h"
#include "Actions/DeleteAllAction.h"

void LightTrailScene::draw(sf::RenderTarget &target) {

    //TODO do drawing here
    sf::RectangleShape rect(sf::Vector2f(2560,1600));
    rect.setFillColor(sf::Color(0,0,0,3));
    texture.draw(rect);

    for(auto &trail : *lightTrails){
        sf::RectangleShape circle(sf::Vector2f(3,3) );
        circle.setPosition(trail->getLocation().x,trail->getLocation().y);
        circle.setFillColor(HueConverter::ToColor(trail->hue));
        texture.draw(circle);
    }

    for(auto &pair : *lightPeople){
        sf::CircleShape circle(10);
        circle.setFillColor(sf::Color::Cyan);
        circle.setPosition(sf::Vector2f(pair.second->getLocation().x,pair.second->getLocation().y));
        texture.draw(circle);
    }

    for(auto &point : *gravityPoints){
        sf::CircleShape gCircle(8);
        gCircle.setFillColor(sf::Color::Red);
        gCircle.setPosition(point->location.x,point->location.y);
        texture.draw(gCircle);
    }

    texture.display();

    target.draw(sf::Sprite(texture.getTexture()));

    //sf::Mouse mouse;
    //sf::Vector2i pos = mouse.getPosition();
    //gravityPoints[0]->location.x = pos.x;
    //gravityPoints[0]->location.y = pos.y;
}

LightTrailScene::LightTrailScene() : Scene(),
                                     lightSources(LightSourceRepository::getInstance()),
                                     lightTrails(LightTrailRepository::getInstance()),
                                     gravityPoints(GravityPointRepository::getInstance()),
                                     colorHoles(ColorHoleRepository::getInstance()),
                                     lightPeople(LightPersonRepository::getInstance())
{
    texture.create(2560,1600);
    //Initialize lists
    lightSources->add(new LightSource(Vector2(0,0),Range(0,90,true),Range(0,90,true),Range(0,400)));
    lightSources->add(new LightSource(Vector2(2560,0),Range(90,180,true),Range(90,180,true),Range(0,400)));
    lightSources->add(new LightSource(Vector2(0,1600),Range(180,270,true),Range(270,0,true),Range(0,400)));
    lightSources->add(new LightSource(Vector2(2560,1600),Range(270,360,true),Range(180,270,true),Range(0,400)));

    actions.push_back(new DeleteAllAction());
    actions.push_back(new UpdateLightTrailsAction());
    actions.push_back(new UpdateLightSourcesAction());
    actions.push_back(new AlternatingGravityPointAction(Range(0,120,true)));
    actions.push_back(new AlternatingGravityPointAction(Range(120,240,true)));
    actions.push_back(new AlternatingGravityPointAction(Range(240,0,true)));

    //conditions.push_back(new PersonTurnedBystanderCondition());
}

void LightTrailScene::updatePeople(vector<Person> newPeople) {
    Range hueDraw(0,360,true);
    for(int i=0;i<newPeople.size();++i){
        Person person = newPeople[i];
        unsigned int id = person.getId();
        if(lightPeople->has(id)){
            LightPerson* lPerson = lightPeople->get(id);
            lPerson->setLocation(person.getLocation());
            lPerson->type = person.type;
        }else{
            float startHue = hueDraw.drawRandom();
            float endHue = startHue+90;
            lightPeople->add(new LightPerson(person.getLocation(),id,person.type,Range(startHue,endHue,true)));
        }
    }

    //TODO remove people when they're gone
}





