//
// Created by Wouter Posdijk on 02/06/16.
//

#include "NoPeopleCondition.h"
#include "../Actions/AlternatingGravityPointAction.h"

int NoPeopleCondition::check(float dt, std::vector<Action *> &actions) {
    int i = 0;
    if(lightPeople->size() == 0 && prevSize != 0){
        Action* action1 = new AlternatingGravityPointAction(util::Range(0, 180, true),
                                                            util::Range(0, config.screenWidth()),
                                                            util::Range(0, config.screenHeight()), gravityPoints,
                                                            lightPeople, lightTrails, config);
        Action* action2 = new AlternatingGravityPointAction(util::Range(180, 0, true),
                                                            util::Range(0, config.screenWidth()),
                                                            util::Range(0, config.screenHeight()), gravityPoints,
                                                            lightPeople, lightTrails, config);
        actions.push_back(action1);
        actions.push_back(action2);
        i = 2;
    }
    prevSize = static_cast<int>(lightPeople->size());
    return i;
}

NoPeopleCondition::NoPeopleCondition(LightPersonRepository *lightPeople, GravityPointRepository *gravityPoints,
                                     const LightTrailSceneConfiguration &config, LightTrailRepository *lightTrails)
        : lightPeople(lightPeople), gravityPoints(gravityPoints),
          config(config), lightTrails(lightTrails) { }