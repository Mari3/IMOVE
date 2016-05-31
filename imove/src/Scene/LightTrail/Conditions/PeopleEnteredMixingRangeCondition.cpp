//
// Created by Wouter Posdijk on 30/05/16.
//

#include "PeopleEnteredMixingRangeCondition.h"
#include "../Actions/MixingAction.h"

PeopleEnteredMixingRangeCondition::PeopleEnteredMixingRangeCondition(LightPersonRepository *lightPeople,
                                                                     LightTrailRepository *lightTrails,
                                                                     GravityPointRepository* gravityPoints,
                                                                     const LightTrailConfiguration &config) :
lightPeople(lightPeople), lightTrails(lightTrails), gravityPoints(gravityPoints), config(config)
{
}

int PeopleEnteredMixingRangeCondition::check(float dt, std::vector<Action *> &actions) {
    int i = 0;
    lightPeople->for_each([&](shared_ptr<LightPerson> person1){
        int j = 0;
        lightPeople->for_each([&](shared_ptr<LightPerson> person2) {
            if (j > i) { // If the people aren't the same and haven't been matched yet
                Vector2 diff = person1->getLocation() - person2->getLocation();
                float dist = diff.size();

                int id1 = person1->getId();
                int id2 = person2->getId();
                if(id2 < id1){
                    int temp = id2;
                    id2 = id1;
                    id1 = temp;
                }

                std::pair<int, int> pair(id1, id2);
                std::set<std::pair<int, int>>::iterator loc = withinRange.find(pair);

                if (dist < config.mixingDistance()) {
                    if (loc != withinRange.end())
                        return;
                    Action* newAction = new MixingAction(person1,person2,lightTrails,gravityPoints,config);
                    actions.push_back(newAction);
                    withinRange.insert(pair);
                } else if (loc != withinRange.end())
                    withinRange.erase(loc);
            }
            j++;
        });
        i++;
    });
    return static_cast<int>(actions.size());
}

