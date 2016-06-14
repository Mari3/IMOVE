//
// Created by Wouter Posdijk on 26/05/16.
//

#include <gtest/gtest.h>
#include "../../../../../src/Scene/LightTrail/LightTrailConfiguration.h"
#include "../../../../../src/Scene/LightTrail/LightPerson.h"
#include "../../../../../src/Scene/LightTrail/Repositories/LightsSceneRepositories.h"
#include "../../../../../src/Scene/LightTrail/Repositories/LightsSceneVectorRepositories.h"
#include "../../../../../src/Scene/LightTrail/Actions/BystanderGravityPointAction.h"
#include "../../../../../../scene_interface/src/Vector2.h"
#include "../../../../../../scene_interface/src/Person.h"

LightTrailConfiguration bgpat_config(800, 600, util::Range(0, 0), util::Range(0, 0), util::Range(0, 0),
                                     util::Range(0, 0), 0, 0, util::Range(0, 0),
                                     500, 100, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0);

TEST (BystanderGravityPointActionTest, UpdateLocation) {

    std::shared_ptr<LightPerson> person(new LightPerson(Location(50,60),1,Person::PersonType::Bystander,util::Range(20,40)));

    GravityPointRepository* gravityPoints = new GravityPointVectorRepository();

    BystanderGravityPointAction action(person,gravityPoints,bgpat_config);

    ASSERT_EQ(gravityPoints->size(),1);

    std::shared_ptr<GravityPoint> gPoint = gravityPoints->get(0);

    ASSERT_FLOAT_EQ(gPoint->location.x,50);
    ASSERT_FLOAT_EQ(gPoint->location.y,60);

    person->setLocation(Vector2(43,75));
    action.execute(6);
    Action* followup = nullptr;
    ASSERT_FALSE(action.isDone(followup));

    ASSERT_FLOAT_EQ(gPoint->location.x,43);
    ASSERT_FLOAT_EQ(gPoint->location.y,75);
}

TEST (BystanderGravityPointActionTest, DoneWhenStatusChanged) {
    std::shared_ptr<LightPerson> person(new LightPerson(Location(50,60),1,Person::PersonType::Bystander,util::Range(20,40)));

    GravityPointRepository* gravityPoints = new GravityPointVectorRepository();

    BystanderGravityPointAction action(person,gravityPoints,bgpat_config);

    person->type = Person::PersonType::Participant;

    Action* followup = nullptr;
    ASSERT_TRUE(action.isDone(followup));

    ASSERT_FALSE(followup);
}

TEST (BystanderGravityPointActionTest, AlternateGravityPoint) {

    std::shared_ptr<LightPerson> person(new LightPerson(Location(50,60),1,Person::PersonType::Bystander,util::Range(20,40)));

    GravityPointRepository* gravityPoints = new GravityPointVectorRepository();

    BystanderGravityPointAction action(person,gravityPoints,bgpat_config);

    ASSERT_EQ(gravityPoints->size(),1);

    action.execute(1.5f);

    gravityPoints->removeAll();

    ASSERT_EQ(gravityPoints->size(),1);

    action.execute(.6f);

    gravityPoints->removeAll();

    ASSERT_EQ(gravityPoints->size(),0);

    action.execute(2.f);

    gravityPoints->removeAll();

    ASSERT_EQ(gravityPoints->size(),1);
}
