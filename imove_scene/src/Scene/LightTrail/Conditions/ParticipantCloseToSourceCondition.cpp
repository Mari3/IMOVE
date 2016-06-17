//
// Created by Wouter Posdijk on 07/06/16.
//

#include "ParticipantCloseToSourceCondition.h"
#include "../Actions/ChangeHueToSourceAction.h"

ParticipantCloseToSourceCondition::ParticipantCloseToSourceCondition(LightPersonRepository *lightPeople,
                                                                     LightSourceRepository *lightSources,
                                                                     const LightSourceConfig &config)
        : lightPeople(lightPeople), lightSources(lightSources), config(config) { }

int ParticipantCloseToSourceCondition::check(float dt, std::vector<Action *> &actions) {
    int i =0;
    lightPeople->for_each([&](std::shared_ptr<LightPerson> person){
        lightSources->for_each([&](std::shared_ptr<LightSource> source){
            if(person->person_type == scene_interface::Person::Participant && !person->isColorHole) {
                float diff = (person->getLocation() - source->getLocation()).size();
                if (diff < config.hueChangeRange) {
                    Action* newAction = new ChangeHueToSourceAction(person,source);
                    actions.push_back(newAction);
                    ++i;
                }
            }
        });
    });
    return i;
}
