//
// Created by Wouter Posdijk on 26/05/16.
//

#include <gtest/gtest.h>
#include "../../../../../src/scene/LightTrail/LightTrailConfiguration.h"
#include "../../../../../src/scene/LightTrail/LightPerson.h"
#include "../../../../../src/scene/LightTrail/Repositories/LightsSceneRepositories.h"
#include "../../../../../src/scene/LightTrail/Repositories/LightsSceneVectorRepositories.h"
#include "../../../../../src/scene/LightTrail/Actions/BystanderGravityPointAction.h"

LightTrailConfiguration bgpat_config(800,600,util::Range(0,0),util::Range(0,0),util::Range(0,0),util::Range(0,0),
                                     0,0,util::Range(0,0),500,100,0,2,0,0,0,0,0,0,0,0);

TEST (BystanderGravityPointActionTest, UpdateLocation) {

    std::shared_ptr<LightPerson> person(new LightPerson(Vector2(50,60),1,Bystander,util::Range(20,40)));

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
    std::shared_ptr<LightPerson> person(new LightPerson(Vector2(50,60),1,Bystander,util::Range(20,40)));

    GravityPointRepository* gravityPoints = new GravityPointVectorRepository();

    BystanderGravityPointAction action(person,gravityPoints,bgpat_config);

    person->type = Participant;

    Action* followup = nullptr;
    ASSERT_TRUE(action.isDone(followup));

    ASSERT_FALSE(followup);
}

TEST (BystanderGravityPointActionTest, AlternateGravityPoint) {

    std::shared_ptr<LightPerson> person(new LightPerson(Vector2(50,60),1,Bystander,util::Range(20,40)));

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