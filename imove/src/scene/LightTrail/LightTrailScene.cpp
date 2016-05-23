//
// Created by Wouter Posdijk on 11/05/16.
//

#include "LightTrailScene.h"
#include "Actions/UpdateLightTrailsAction.h"
#include "../Util/HueConverter.h"
#include "Actions/UpdateLightSourcesAction.h"
#include "Actions/AlternatingGravityPointAction.h"
#include "Conditions/PersonChangedTypeCondition.h"
#include "Actions/DeleteAllAction.h"

void LightTrailScene::draw(sf::RenderTarget &target) {

    //Slightly fade the current texture
    sf::RectangleShape rect(sf::Vector2f(800, 600));
    rect.setFillColor(sf::Color(0, 0, 0, 10));
    texture.draw(rect);

    //Draw all light trails on the texture
    for(auto &trail : *lightTrails){
        sf::RectangleShape circle(sf::Vector2f(3, 3) );
        circle.setPosition(trail->getLocation().x,trail->getLocation().y);
        circle.setFillColor(HueConverter::ToColor(trail->hue));
        texture.draw(circle);
    }

    //Draw all people on the target (for debugging purposes)
    for(auto &pair : *lightPeople){
        sf::CircleShape circle(5);
        circle.setFillColor(sf::Color::Cyan);
        circle.setPosition(sf::Vector2f(pair.second->getLocation().x,pair.second->getLocation().y));
        target.draw(circle);
    }

    //Draw all gravitypoints on the target (for debugging purposes)
    for(auto &point : *gravityPoints){
        sf::CircleShape gCircle(4);
        gCircle.setFillColor(sf::Color::Red);
        gCircle.setPosition(point->location.x,point->location.y);
        target.draw(gCircle);
    }

    //Draw the texture onto the target
    texture.display();
    target.draw(sf::Sprite(texture.getTexture()));

}

LightTrailScene::LightTrailScene() : Scene(),
                                     lightSources(LightSourceRepository::getInstance()),
                                     lightTrails(LightTrailRepository::getInstance()),
                                     gravityPoints(GravityPointRepository::getInstance()),
                                     colorHoles(ColorHoleRepository::getInstance()),
                                     lightPeople(LightPersonRepository::getInstance())
{
    //Initialize the light trail texture
    texture.create(800,600);

    //Add Light sources on every corner
    lightSources->add(new LightSource(Vector2(0, 0),util::Range(0, 90,true),util::Range(0, 90,true),util::Range(0,100)));
    lightSources->add(new LightSource(Vector2(800,0),util::Range(90,180,true),util::Range(90, 180,true),util::Range(0,100)));
    lightSources->add(new LightSource(Vector2(0, 600),util::Range(180, 270,true),util::Range(270, 0,true),util::Range(0,100)));
    lightSources->add(new LightSource(Vector2(800, 600),util::Range(270, 360,true),util::Range(180, 270,true),util::Range(0,100)));


    //Add all the basic actions
    actions.push_back(new DeleteAllAction());
    actions.push_back(new UpdateLightTrailsAction());
    actions.push_back(new UpdateLightSourcesAction());
    actions.push_back(new AlternatingGravityPointAction());
    actions.push_back(new AlternatingGravityPointAction());

    //Add all conditions
    conditions.push_back(new PersonChangedTypeCondition());
}

void LightTrailScene::processPeople() {
    if(!peopleQueue.empty()) { //If people have been updated

        //Get the first update and pop it.
        vector<Person> newPeople = peopleQueue.front();
        peopleQueue.pop();

        //Set up tracking of people that are gone
        map<unsigned int,bool> existingPeople;

        //Set up range for generating new hues
        util::Range hueDraw(0, 360, true);

        for (int i = 0; i < newPeople.size(); ++i) {

            Person person = newPeople[i];
            unsigned int id = person.getId();
            existingPeople[id] = true;

            if (lightPeople->has(id)) { //If the person currently exists

                //Update the person
                LightPerson *lPerson = lightPeople->get(id);
                lPerson->setLocation(person.getLocation());
                lPerson->type = person.type;

            } else {

                //Create a new person with randomly generated hue
                float startHue = hueDraw.drawRandom();
                float endHue = startHue + 90;
                lightPeople->add(
                        new LightPerson(person.getLocation(), id, person.type, util::Range(startHue, endHue, true)));

            }
        }
        for(auto &pair : *lightPeople){

            if(!existingPeople[pair.first]){ //If this person does not exist anymore
                pair.second->type = None;

                //Remove it from the list
                lightPeople->scheduleForRemoval(pair.second);
            }
        }
    }

    //TODO remove people when they're gone
}





