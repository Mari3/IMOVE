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
        if((oldPersonType.count(person->getId()) == 0 || oldPersonType[person->getId()] != scene_interface::Person::PersonType::Bystander) && person->person_type == scene_interface::Person::PersonType::Bystander){
            // Create a new bystander action
            i++;
            actions.push_back(new BystanderGravityPointAction(person,lightSources,new LightTrailVectorRepository(),
                                                              lightTrails,
                                                              config,texture));
        } // Else if the person turned particpant
        else if((oldPersonType.count(person->getId()) == 0 || oldPersonType[person->getId()] != scene_interface::Person::PersonType::Participant) && person->person_type == scene_interface::Person::PersonType::Participant)
        {
						std::cerr << person->getLocation().x << "," << person->getLocation().y << std::endl; 
						std::cerr << "1PGPA: " << person->getLocation().x << "," << person->getLocation().y << " lb: " << person->hue.lowerBound << " ub: " << person->hue.upperBound << std::endl; 
            // Create a new participant action
            i += 2;
            actions.push_back(new ParticipantGravityPointAction(person,gravityPoints,config));
            if((oldPersonType.count(person->getId()) == 0 || oldPersonType[person->getId()] != scene_interface::Person::PersonType::Bystander)) {
                actions.push_back(
                        new InitiateParticipantAction(lightTrails, new LightTrailVectorRepository(), lightSources,
                                                      person, config, texture));
            }
        }
        oldPersonType[person->getId()] = person->person_type;
        oldMovementType[person->getId()] = person->movement_type;
    });
    return i;
}

PersonChangedTypeCondition::PersonChangedTypeCondition(LightPersonRepository *lightPeople,
                                                       GravityPointRepository *gravityPoints,
                                                       LightTrailRepository *lightTrails,
                                                       LightSourceRepository *lightSources,
                                                       const LightTrailSceneConfiguration &config,
                                                       sf::RenderTexture &texture) :
        lightPeople(lightPeople),
        gravityPoints(gravityPoints),
        lightTrails(lightTrails), lightSources(lightSources),
        config(config), texture(texture) {

}

