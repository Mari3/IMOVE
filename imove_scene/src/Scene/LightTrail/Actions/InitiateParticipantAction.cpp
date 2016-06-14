//
// Created by Wouter Posdijk on 10/06/16.
//

#include <math.h>
#include "InitiateParticipantAction.h"

InitiateParticipantAction::InitiateParticipantAction(LightTrailRepository *globalTrails, LightTrailRepository *myTrails,
                                                     LightSourceRepository *sources, const std::shared_ptr<LightPerson> &person,
                                                     const LightTrailSceneConfiguration& config, sf::RenderTexture &texture
) : globalTrails(globalTrails), myTrails(myTrails), sources(sources), person(person),
    gravityPoint(person->getLocation(),person->hue,config.gravity().participant().gravity),
    config(config), effect(myTrails,config,texture) {

    sources->for_each([&](std::shared_ptr<LightSource> source){
        if(fabsf(source->getHue().getCenter() - person->hue.getCenter()) < 45){
            for(int i=0;i<10;++i) {
                myTrails->add(std::shared_ptr<LightTrail>(source->sendOut()));
            }
        }
    });

}

bool InitiateParticipantAction::isDone(std::vector<Action *> &followUp) {
    bool done = true;

    //TODO replace with find_if
    myTrails->for_each([&](std::shared_ptr<LightTrail> trail){
        float dist = (trail->location-person->getLocation()).size();
        if(dist > 200)
            done = false;
    });

    if(done){
        myTrails->for_each([&](std::shared_ptr<LightTrail> trail){
            globalTrails->add(trail);
        });
        return true;
    }
    return false;
}

void InitiateParticipantAction::execute(float dt) {

    gravityPoint.location = person->getLocation();
    gravityPoint.hue = person->hue;

    myTrails->for_each([&](std::shared_ptr<LightTrail> trail){
        Vector2 force = gravityPoint.calculateForce(*trail,config);
        trail->applyForce(force,dt,config.trail().trail().speedCap,config.trail().sidesEnabled(),config.screenWidth(),config.screenHeight());
    });

}

void InitiateParticipantAction::draw(sf::RenderTarget &target) {
    effect.draw(target);
}