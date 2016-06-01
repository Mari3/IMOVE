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
#include "Conditions/PeopleEnteredMixingRangeCondition.h"
#include "Repositories/LightsSceneVectorRepositories.h"
#include "Actions/LightSourceEffectAction.h"

void LightTrailScene::draw(sf::RenderTarget &target) {

    //Slightly fade the current texture
    sf::RectangleShape rect(sf::Vector2f(config.screenWidth(), config.screenHeight()));
    rect.setFillColor(sf::Color(0, 0, 0, config.fade()));
    texture.draw(rect);

    std::function<void(std::shared_ptr<LightTrail>)> func = [&](std::shared_ptr<LightTrail> trail){

        sf::RectangleShape circle(sf::Vector2f(config.trailThickness(), config.trailThickness()) );
        circle.setPosition(trail->getLocation().x,trail->getLocation().y);
        circle.setFillColor(HueConverter::ToColor(trail->hue));
        texture.draw(circle);

    };

    //Draw all light trails on the texture
    lightTrails->for_each(func);

    for(auto &trails : sourceTrails){
        trails->for_each(func);
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
    gravityPoints->for_each([&](std::shared_ptr<GravityPoint> point){

        sf::CircleShape gCircle(4);
        gCircle.setFillColor(sf::Color::Red);
        gCircle.setPosition(point->location.x,point->location.y);
        target.draw(gCircle);

    });

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
    hueCounter = 0;

    //Initialize the light trail texture
    texture.create(config.screenWidth(),config.screenHeight());

    //Add Light sources on every corner
    lightSources->add(std::shared_ptr<LightSource>(
            new LightSource(Vector2(0, 0),config.cornerHues()[0],
                            util::Range(0, 90,true),config.sendOutSpeed())));
    lightSources->add(std::shared_ptr<LightSource>(
            new LightSource(Vector2(config.screenWidth(),0),config.cornerHues()[1],
                            util::Range(90, 180,true),config.sendOutSpeed())));
    lightSources->add(std::shared_ptr<LightSource>(
            new LightSource(Vector2(0, config.screenHeight()),config.cornerHues()[2],
                            util::Range(270, 0,true),config.sendOutSpeed())));
    lightSources->add(std::shared_ptr<LightSource>(
            new LightSource(Vector2(config.screenWidth(), config.screenHeight()),config.cornerHues()[3],
                            util::Range(180, 270,true),config.sendOutSpeed())));

    for(int i=0;i<4;++i){
        LightTrailRepository* sourceRepo = new LightTrailVectorRepository();
        Action* sourceAction = new LightSourceEffectAction(lightSources->get(i),sourceRepo,config);
        sourceTrails.push_back(sourceRepo);
        actions.push_back(unique_ptr<Action>(sourceAction));
    }


    //Add all the basic actions
    actions.push_back(std::unique_ptr<Action>(
            static_cast<Action*>(new DeleteAllAction(colorHoles,gravityPoints,lightPeople,lightSources,lightTrails))));
    actions.push_back(std::unique_ptr<Action>(
            static_cast<Action*>(new UpdateLightTrailsAction(lightTrails,gravityPoints,config))));
    actions.push_back(std::unique_ptr<Action>(
            static_cast<Action*>(new UpdateLightSourcesAction(lightSources,lightTrails,config))));
    actions.push_back(std::unique_ptr<Action>(
            static_cast<Action*>(new AlternatingGravityPointAction(util::Range(0,180,true),
                                                        util::Range(0,config.screenWidth()),
                                                        util::Range(0,config.screenHeight()),
                                                        gravityPoints,lightPeople,config))));
    actions.push_back(std::unique_ptr<Action>(
            static_cast<Action*>(new AlternatingGravityPointAction(util::Range(180,0,true),
                                                        util::Range(0,config.screenWidth()),
                                                        util::Range(0,config.screenHeight()),
                                                        gravityPoints,lightPeople,config))));

    //Add all conditions
    conditions.push_back(std::unique_ptr<Condition>(
            static_cast<Condition*>(new PersonChangedTypeCondition(lightPeople,gravityPoints,config))));
    conditions.push_back(std::unique_ptr<Condition>(
            static_cast<Condition*>(new PeopleEnteredMixingRangeCondition(lightPeople,lightTrails,gravityPoints,config))
    ));
}

void LightTrailScene::processPeople() {
    if(!peopleQueue.empty()) { //If people have been updated

        //Get the first update and pop it.
        vector<Person> newPeople = peopleQueue.front();
        peopleQueue.pop();

        //Set up range for generating new hues
        util::Range hueDraw(0, 360, true);

        for (unsigned int i = 0; i < newPeople.size(); ++i) {

            Person person = newPeople[i];
            unsigned int id = person.getId();

            if (lightPeople->has(id)) { //If the person currently exists

                //Update the person
                std::shared_ptr<LightPerson> lPerson = lightPeople->get(id);
                lPerson->setLocation(person.getLocation());
                lPerson->type = person.type;

            } else {

                //Create a new person with randomly generated hue
                util::Range hue = config.cornerHues()[hueCounter];
								std::cerr << "lb :" << hue.lowerBound << "ub: " << hue.upperBound << "hueCounter: " << hueCounter << std::endl;
                lightPeople->add(
                        std::shared_ptr<LightPerson>(new LightPerson(person.getLocation(), id, person.type, hue)));
								hueCounter = (hueCounter + 1) % 4;

            }
        }
        lightPeople->for_each([&](std::shared_ptr<LightPerson> person){
            if(person->type == None){ //If this person does not exist anymore

                //Remove it from the list
                lightPeople->scheduleForRemoval(person);
            }
        });
    }
}





