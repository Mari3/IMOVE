#include <vector>
#include <memory>
#include <assert.h>
#include "../../../../scene_interface/src/Vector2.h"
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
#include "Conditions/FirstParticipantCondition.h"
#include "Conditions/NoPeopleCondition.h"
#include "Actions/LightSourceGravityPointAction.h"
#include "Conditions/ColorHoleTimerCondition.h"
#include "Conditions/ParticipantCloseToSourceCondition.h"

void LightTrailScene::draw(sf::RenderTarget &target) {

    //Slightly fade the current texture
    sf::RectangleShape rect(sf::Vector2f(config.screenWidth(), config.screenHeight()));
    rect.setFillColor(sf::Color(0, 0, 0, config.fade()));
    texture.draw(rect);

    effect.draw(target);

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

    /*colorHoles->for_each([&](std::shared_ptr<ColorHole> hole){
        sf::CircleShape hCircle(20);
        hCircle.setFillColor(HueConverter::ToColor(hole->hue.getCenter()));
        hCircle.setPosition(sf::Vector2f(hole->location.x-20,hole->location.y-20));
        target.draw(hCircle);
    });*/

    for(auto &action : actions){
        action->draw(target);
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
                                     config(config),
                                      effect(lightTrails,config,texture)
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
    texture.clear(sf::Color::Black);

    //Add Light sources on every corner
    lightSources->add(std::shared_ptr<LightSource>(
            new LightSource(Vector2(0, 0), config.cornerHues()[0], util::Range(0, 90, true),
                            config.sendOutSpeed(), config.sendOutDelay()*config.trailCap()/4.f)));
    lightSources->add(std::shared_ptr<LightSource>(
            new LightSource(Vector2(config.screenWidth(), 0), config.cornerHues()[1], util::Range(90, 180, true),
                            config.sendOutSpeed(), config.sendOutDelay()*config.trailCap()/4.f)));
    lightSources->add(std::shared_ptr<LightSource>(
            new LightSource(Vector2(0, config.screenHeight()), config.cornerHues()[2], util::Range(270, 0, true),
                            config.sendOutSpeed(), config.sendOutDelay()*config.trailCap()/4.f)));
    lightSources->add(std::shared_ptr<LightSource>(
            new LightSource(Vector2(config.screenWidth(), config.screenHeight()), config.cornerHues()[3],
                            util::Range(180, 270, true),
                            config.sendOutSpeed(), config.sendOutDelay()*config.trailCap()/4.f)));

    for(int i=0;i<4;++i){
        LightTrailRepository* sourceRepo = new LightTrailVectorRepository();
        Action* sourceAction = new LightSourceEffectAction(lightSources->get(i),sourceRepo,config,texture);
        sourceTrails.push_back(sourceRepo);
        actions.push_back(std::unique_ptr<Action>(sourceAction));
    }


    //Add all the basic actions
    actions.push_back(std::unique_ptr<Action>(
            static_cast<Action*>(new DeleteAllAction(colorHoles,gravityPoints,lightPeople,lightSources,lightTrails))));
    actions.push_back(std::unique_ptr<Action>(
            static_cast<Action*>(new UpdateLightTrailsAction(lightTrails,gravityPoints,config))));
    actions.push_back(std::unique_ptr<Action>(
            static_cast<Action*>(new UpdateLightSourcesAction(lightSources,lightTrails,config))));
    actions.push_back(std::unique_ptr<Action>(
            static_cast<Action*>(new LightSourceGravityPointAction(lightPeople,gravityPoints,config))
    ));

    //Add all conditions
    conditions.push_back(std::unique_ptr<Condition>(
            static_cast<Condition*>(new PersonChangedTypeCondition(lightPeople, gravityPoints, lightTrails,
                                                                   lightSources, config, texture))));
    conditions.push_back(std::unique_ptr<Condition>(
            static_cast<Condition*>(new PeopleEnteredMixingRangeCondition(lightPeople,lightTrails,gravityPoints,config))
    ));
    /*conditions.push_back(std::unique_ptr<Condition>(
            static_cast<Condition*>(new FirstParticipantCondition(lightPeople,config,gravityPoints))
    ));*/
    conditions.push_back(std::unique_ptr<Condition>(
            static_cast<Condition*>(new NoPeopleCondition(lightPeople, gravityPoints, config, lightTrails))
    ));
    conditions.push_back(std::unique_ptr<Condition>(
            static_cast<Condition*>(new ColorHoleTimerCondition(colorHoles,lightPeople,config,lightTrails,gravityPoints))
    ));
    conditions.push_back(std::unique_ptr<Condition>(
            static_cast<Condition*>(new ParticipantCloseToSourceCondition(lightPeople,lightSources,config))
    ));
}

void LightTrailScene::processPeople() {
    if(!peopleQueue.empty()) { //If people have been updated

        //Get the first update and pop it.
        std::vector<Person> newPeople = peopleQueue.front();
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

            } else if(person.type != None) {

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





