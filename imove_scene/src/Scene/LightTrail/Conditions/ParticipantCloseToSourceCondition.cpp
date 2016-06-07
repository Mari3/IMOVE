//
// Created by Wouter Posdijk on 07/06/16.
//

#include "ParticipantCloseToSourceCondition.h"
#include "../Actions/ChangeHueToSourceAction.h"

ParticipantCloseToSourceCondition::ParticipantCloseToSourceCondition(LightPersonRepository *lightPeople,
                                                                     LightSourceRepository *lightSources,
                                                                     const LightTrailConfiguration &config)
        : lightPeople(lightPeople), config(config), lightSources(lightSources) { }

int ParticipantCloseToSourceCondition::check(float dt, std::vector<Action *> &actions) {
    int i =0;
    lightPeople->for_each([&](std::shared_ptr<LightPerson> person){
        lightSources->for_each([&](std::shared_ptr<LightSource> source){
            if(person->type == Participant || person->type == StandingStill) {
                float diff = (person->getLocation() - source->getLocation()).size();
                if (diff < 100.f) {
                    Action* newAction = new ChangeHueToSourceAction(person,source);
                    actions.push_back(newAction);
                    ++i;
                }
            }
        });
    });
    return i;
}