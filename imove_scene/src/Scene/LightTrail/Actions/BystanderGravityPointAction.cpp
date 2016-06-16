#include <math.h>
#include "BystanderGravityPointAction.h"
#include "../Configuration/LightTrailSceneConfiguration.h"
#include "../../../../../scene_interface/src/Person.h"
#include "../Repositories/LightsSceneVectorRepositories.h"
#include "InitiateParticipantAction.h"

BystanderGravityPointAction::BystanderGravityPointAction(std::shared_ptr<LightPerson> person,
                                                         LightSourceRepository *sources,
                                                         LightTrailRepository *myTrails,
                                                         LightTrailRepository *globalTrails,
                                                         const LightTrailSceneConfiguration &config,
                                                         sf::RenderTexture &texture)
  :
        person(person),
        timer(Timer(config.gravity().bystander().delay, true)),
        config(config),
        myTrails(myTrails),
        globalTrails(globalTrails), texture(texture) {
    gravityPoint = std::shared_ptr<GravityPoint>(new GravityPoint(Vector2(0,0),person->hue,config.gravity().bystander().gravity,
    config.gravity().bystander().range));
    setLocation();


    sources->for_each([&](std::shared_ptr<LightSource> source){
        if(fabsf(source->getHue().getCenter() - person->hue.getCenter()) < 45){
            for(int i=0;i<10;++i) {
                myTrails->add(std::shared_ptr<LightTrail>(source->sendOut()));
                person->initiativeTrailCount++;
            }
        }
    });

    gravityPointActive = true;

    effects.push_back(std::unique_ptr<Effect>(
        static_cast<Effect*>(new LightTrailEffect(myTrails,config,texture))
    ));
}

void BystanderGravityPointAction::setLocation() {
    float x = person->getLocation().x;
    float y = person->getLocation().y;
    float gX = x;
    float gY = y;

    //Keep the x and y within the screen
    if(x < 0){
        gX = 0;
    }else if(x > config.screenWidth()){
        gX = config.screenWidth();
    }
    if(y < 0){
        gY = 0;
    }else if(y > config.screenHeight()){
        gY = config.screenHeight();
    }

    gravityPoint->location.x = gX;
    gravityPoint->location.y = gY;
}


bool BystanderGravityPointAction::isDone(std::vector<Action*> &followUp) {
    //This action is done when the person it tracks is not a bystander anymore
    if(person->person_type == scene_interface::Person::PersonType::Participant){
        followUp.push_back(
                new InitiateParticipantAction(globalTrails,myTrails,sources,person,config,texture)
        );
        return true;
    }
    return person->person_type != scene_interface::Person::PersonType::Bystander;
}

void BystanderGravityPointAction::execute(float dt) {
    setLocation();

    if(timer.update(dt)){ //If the timer is done
        //Switch the gravity point on or off
        if(gravityPointActive){
            //gravityPoints->scheduleForRemoval(gravityPoint);
            gravityPoint->gravity = 0;
            gravityPointActive = false;
        }else{
            //gravityPoints->add(gravityPoint);
            gravityPoint->gravity = config.gravity().bystander().gravity;
            gravityPointActive = true;
        }
    }

    myTrails->for_each([&](std::shared_ptr<LightTrail> trail){
        Vector2 force = gravityPoint->calculateForce(*trail,config);
        trail->applyForce(force,dt,config.trail().trail().speedCap,config.trail().sidesEnabled(),config.screenWidth(),
                          config.screenHeight());
    });
}
