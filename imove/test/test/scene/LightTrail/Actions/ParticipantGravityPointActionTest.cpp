//
// Created by Wouter Posdijk on 26/05/16.
//

#include <gtest/gtest.h>
#include "../../../../../src/Scene/LightTrail/LightTrailConfiguration.h"
#include "../../../../../src/Scene/LightTrail/LightPerson.h"
#include "../../../../../src/Scene/LightTrail/Repositories/LightsSceneRepositories.h"
#include "../../../../../src/Scene/LightTrail/Repositories/LightsSceneVectorRepositories.h"
#include "../../../../../src/Scene/LightTrail/Actions/ParticipantGravityPointAction.h"

LightTrailConfiguration pgpat_config(800,600,util::Range(0,0),util::Range(0,0),util::Range(0,0),util::Range(0,0),
0,0,util::Range(0,0),500,100,0,0,0,0,0,0,0,0,0,0);

TEST (ParticipantGravityPointActionTest, UpdateLocation) {

    std::shared_ptr<LightPerson> person(new LightPerson(Vector2(50,60),1,Participant,util::Range(20,40)));

    GravityPointRepository* gravityPoints = new GravityPointVectorRepository();

    ParticipantGravityPointAction action(person,gravityPoints,pgpat_config);

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

TEST (ParticipantGravityPointActionTest, DoneWhenStatusChanged) {
    std::shared_ptr<LightPerson> person(new LightPerson(Vector2(50,60),1,Participant,util::Range(20,40)));

    GravityPointRepository* gravityPoints = new GravityPointVectorRepository();

    ParticipantGravityPointAction action(person,gravityPoints,pgpat_config);

    person->type = Bystander;

    Action* followup = nullptr;
    ASSERT_TRUE(action.isDone(followup));

    ASSERT_FALSE(followup);
}