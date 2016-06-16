//
// Created by Wouter Posdijk on 16/06/16.
//

#include "PersonDisappearedCondition.h"
#include "../Actions/RemoveTrailsAction.h"

PersonDisappearedCondition::PersonDisappearedCondition(LightPersonRepository *lightPeople, LightTrailRepository *trails,
                                                       const LightTrailSceneConfiguration &config)
        : lightPeople(lightPeople), trails(trails),
          config(config) { }

int PersonDisappearedCondition::check(float dt, std::vector<Action *> &actions) {
    lightPeople->for_each([&] (std::shared_ptr<LightPerson> person){
        if(person->person_type == scene_interface::Person::PersonType::None){
            actions.push_back(new RemoveTrailsAction(person,trails,config));
        }
    });
    return static_cast<int>(actions.size());
}