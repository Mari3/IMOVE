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
    config(config) {

    sources->for_each([&](std::shared_ptr<LightSource> source){
        if(fabsf(source->getHue().getCenter() - person->hue.getCenter()) < 45){
            int amount = config.effect().trail().participantInitAmount-static_cast<int>(myTrails->size());
            for(unsigned int i=0;i<amount;++i) {
                myTrails->add(std::shared_ptr<LightTrail>(source->sendOut()));
                person->initiativeTrailCount++;
            }
        }
    });

    effects.push_back(std::unique_ptr<Effect>(
        static_cast<Effect*>(new LightTrailEffect(myTrails,config,texture))
    ));

}

bool InitiateParticipantAction::isDone(std::vector<Action *> &followUp) {
    return person->person_type != scene_interface::Person::Participant || myTrails->size() == 0;
}

void InitiateParticipantAction::execute(float dt) {

    gravityPoint.location = person->getLocation();
    gravityPoint.hue = person->hue;

    myTrails->for_each([&](std::shared_ptr<LightTrail> trail){
        Vector2 force = gravityPoint.calculateForce(*trail,config);
        trail->applyForce(force,dt,config.trail().trail().speedCap,config.trail().sidesEnabled(),config.screenWidth(),config.screenHeight());

        float dist = (trail->location-person->getLocation()).size();
        if(dist < config.effect().trail().initRange) {
            globalTrails->add(trail);
            myTrails->scheduleForRemoval(trail);
            person->initiativeTrailCount--;
        }
    });
    myTrails->removeAll();

}
