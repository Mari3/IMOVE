//
// Created by Wouter Posdijk on 30/05/16.
//

#include "PeopleEnteredMixingRangeCondition.h"

PeopleEnteredMixingRangeCondition::PeopleEnteredMixingRangeCondition(LightPersonRepository *lightPeople,
                                                                     const LightTrailConfiguration &config) :
lightPeople(lightPeople), config(config)
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

                std::pair<int, int> pair(person1->getId(), person2->getId());
                std::set<std::pair<int, int>>::iterator loc = withinRange.find(pair);

                if (dist < 512) { // TODO replace with config
                    if (loc < withinRange.end())
                        return;
                    //TODO create new mixing action
                    withinRange.insert(pair);
                } else if (loc < withinRange.end())
                    withinRange.erase(loc);
            }
            j++;
        });
        i++;
    });
}

