#include "PersonChangedTypeCondition.h"
#include <memory>
#include <iostream>
#include "../Actions/BystanderGravityPointAction.h"
#include "../Actions/ParticipantGravityPointAction.h"
#include "../Actions/InitiateParticipantAction.h"
#include "../Repositories/LightsSceneVectorRepositories.h"

int PersonChangedTypeCondition::check(float dt, std::vector<Action*> &actions) {
    int i = 0;
    lightPeople->for_each([&](std::shared_ptr<LightPerson> person){
        // If the person turned bystander
        if((oldType.count(person->getId()) == 0 || oldType[person->getId()] != Bystander) && person->type == Bystander){
            // Create a new bystander action
            i++;
            actions.push_back(new BystanderGravityPointAction(person,gravityPoints,config));
        } // Else if the person turned particpant
        else if((oldType.count(person->getId()) == 0 || (oldType[person->getId()] != Participant && oldType[person->getId()] != StandingStill)) && (person->type == Participant || person->type == StandingStill))
        {
						std::cerr << person->getLocation().x << "," << person->getLocation().y << std::endl; 
						std::cerr << "1PGPA: " << person->getLocation().x << "," << person->getLocation().y << " lb: " << person->hue.lowerBound << " ub: " << person->hue.upperBound << std::endl; 
            // Create a new participant action
            i += 2;
            actions.push_back(new ParticipantGravityPointAction(person,gravityPoints,config));
            actions.push_back(new InitiateParticipantAction(lightTrails,new LightTrailVectorRepository(),lightSources,person,config,texture));
        }
        oldType[person->getId()] = person->type;
    });
    return i;
}

PersonChangedTypeCondition::PersonChangedTypeCondition(LightPersonRepository *lightPeople,
                                                       GravityPointRepository *gravityPoints,
                                                       LightTrailRepository *lightTrails,
                                                       LightSourceRepository *lightSources,
                                                       const LightTrailConfiguration &config,
                                                       sf::RenderTexture &texture) :
        lightPeople(lightPeople),
        gravityPoints(gravityPoints),
        lightTrails(lightTrails), lightSources(lightSources),
        config(config), texture(texture) {

}

