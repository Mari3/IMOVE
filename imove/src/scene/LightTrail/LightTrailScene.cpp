//
// Created by Wouter Posdijk on 11/05/16.
//

#include <memory>
#include <assert.h>
#include "LightTrailScene.h"
#include "Actions/UpdateLightTrailsAction.h"
#include "../Util/HueConverter.h"
#include "Actions/UpdateLightSourcesAction.h"
#include "Actions/AlternatingGravityPointAction.h"
#include "Conditions/PersonChangedTypeCondition.h"
#include "Actions/DeleteAllAction.h"

void LightTrailScene::draw(sf::RenderTarget &target) {

    //Slightly fade the current texture
    sf::RectangleShape rect(sf::Vector2f(config.screenWidth(), config.screenHeight()));
    rect.setFillColor(sf::Color(0, 0, 0, config.fade()));
    texture.draw(rect);

    //Draw all light trails on the texture
    for(auto &trail : *lightTrails){
        sf::RectangleShape circle(sf::Vector2f(config.trailThickness(), config.trailThickness()) );
        circle.setPosition(trail->getLocation().x,trail->getLocation().y);
        circle.setFillColor(HueConverter::ToColor(trail->hue));
        texture.draw(circle);
    }

    //Draw the texture onto the target
    texture.display();
    target.draw(sf::Sprite(texture.getTexture()));

    //Draw all people on the target (for debugging purposes)
    lightPeople->for_each([&](std::shared_ptr<LightPerson> person){
        sf::CircleShape circle(5);
        circle.setFillColor(sf::Color::Cyan);
        circle.setPosition(sf::Vector2f(person->getLocation().x,person->getLocation().y));
        target.draw(circle);
    });

    //Draw all gravitypoints on the target (for debugging purposes)
    for(auto &point : *gravityPoints){
        sf::CircleShape gCircle(4);
        gCircle.setFillColor(sf::Color::Red);
        gCircle.setPosition(point->location.x,point->location.y);
        target.draw(gCircle);
    }

}

LightTrailScene::LightTrailScene(const LightTrailConfiguration &config,
LightSourceRepository* lightSources, LightTrailRepository* lightTrails,
GravityPointRepository* gravityPoints, ColorHoleRepository* colorHoles,
LightPersonRepository* lightPeople) : Scene(),
                                     lightSources(lightSources),
                                     lightTrails(lightTrails),
                                     gravityPoints(gravityPoints),
                                     colorHoles(colorHoles),
                                     lightPeople(lightPeople),
                                     config(config)
{
    //Make sure that the repostories are not null
    assert(lightSources);
    assert(lightTrails);
    assert(gravityPoints);
    assert(colorHoles);
    assert(lightPeople);

    //Initialize the light trail texture
    texture.create(config.screenWidth(),config.screenHeight());

    //Add Light sources on every corner
    lightSources->add(std::shared_ptr<LightSource>(
            new LightSource(Vector2(0, 0),config.corner1Hue(),
                            util::Range(0, 90,true),config.sendOutSpeed())));
    lightSources->add(std::shared_ptr<LightSource>(
            new LightSource(Vector2(config.screenWidth(),0),config.corner2Hue(),
                            util::Range(90, 180,true),config.sendOutSpeed())));
    lightSources->add(std::shared_ptr<LightSource>(
            new LightSource(Vector2(0, config.screenHeight()),config.corner3Hue(),
                            util::Range(270, 0,true),config.sendOutSpeed())));
    lightSources->add(std::shared_ptr<LightSource>(
            new LightSource(Vector2(config.screenWidth(), config.screenHeight()),config.corner4Hue(),
                            util::Range(180, 270,true),config.sendOutSpeed())));


    //Add all the basic actions
    actions.push_back(new DeleteAllAction(colorHoles,gravityPoints,lightPeople,lightSources,lightTrails));
    actions.push_back(new UpdateLightTrailsAction(lightTrails,gravityPoints,config));
    actions.push_back(new UpdateLightSourcesAction(lightSources,lightTrails,config));
    actions.push_back(new AlternatingGravityPointAction(util::Range(0,180,true),
                                                        util::Range(0,config.screenWidth()),
                                                        util::Range(0,config.screenHeight()),
                                                        gravityPoints,lightPeople,config));
    actions.push_back(new AlternatingGravityPointAction(util::Range(180,0,true),
                                                        util::Range(0,config.screenWidth()),
                                                        util::Range(0,config.screenHeight()),
                                                        gravityPoints,lightPeople,config));

    //Add all conditions
    conditions.push_back(new PersonChangedTypeCondition(lightPeople,gravityPoints,config));
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
                std::shared_ptr<LightPerson> lPerson = lightPeople->get(id);
                lPerson->setLocation(person.getLocation());
                lPerson->type = person.type;

            } else {

                //Create a new person with randomly generated hue
                float startHue = hueDraw.drawRandom();
                float endHue = startHue + 90;
                lightPeople->add(
                        std::shared_ptr<LightPerson>(new LightPerson(person.getLocation(), id, person.type, util::Range(startHue, endHue, true))));

            }
        }
        lightPeople->for_each([&](std::shared_ptr<LightPerson> person){
            if(existingPeople.count(person->getId()) == 0){ //If this person does not exist anymore
                person->type = None;

                //Remove it from the list
                lightPeople->scheduleForRemoval(person);
            }
        });
    }

    //TODO remove people when they're gone
}





