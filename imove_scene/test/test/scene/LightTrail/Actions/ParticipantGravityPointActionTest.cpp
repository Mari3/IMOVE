//
// Created by Wouter Posdijk on 26/05/16.
//

#include <gtest/gtest.h>
<<<<<<< 06aee995ed42b7f05c320c1bec41f7877dc357ba
#include <vector>
#include "../../../../../src/Scene/LightTrail/Configuration/LightTrailConfiguration.h"
=======
#include "../../../../../src/Scene/LightTrail/Configuration/LightTrailSceneConfiguration.h"
>>>>>>> Refactor configuration
#include "../../../../../src/Scene/LightTrail/LightPerson.h"
#include "../../../../../src/Scene/LightTrail/Repositories/LightsSceneRepositories.h"
#include "../../../../../src/Scene/LightTrail/Repositories/LightsSceneVectorRepositories.h"
#include "../../../../../src/Scene/LightTrail/Actions/ParticipantGravityPointAction.h"
#include "../../../../../../imove_imp/src/Vector2.h"
#include "../../../../../../scene_interface/src/Person.h"

<<<<<<< 06aee995ed42b7f05c320c1bec41f7877dc357ba
LightTrailConfiguration pgpat_config(0, 0, std::vector<util::Range>(), LightSourceConfig(), ParticipantGravityConfig(),
        DelayGravityConfig(), DelayGravityConfig(), ProximityConfig(), false, TrailConfig(),
0, MixingConfig(), ExplosionConfig(), GravityConfig(), ColorHoleConfig(),
        StarConfig(), 0);
=======
LightTrailSceneConfiguration pgpat_config(0, 0, util::Range(0, 0), util::Range(0, 0), util::Range(0, 0), util::Range(0, 0),
                                     0,
                                     0, util::Range(0, 0), 0, 0, 0, 0, 0,
                                     0, (StarConfig()), 0);
>>>>>>> Refactor configuration

TEST (ParticipantGravityPointActionTest, UpdateLocation) {

    std::shared_ptr<LightPerson> person(new LightPerson(Location(50,60),1,Person::PersonType::Participant,util::Range(20,40)));

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
    std::shared_ptr<LightPerson> person(new LightPerson(Location(50,60),1,Person::PersonType::Participant,util::Range(20,40)));

    GravityPointRepository* gravityPoints = new GravityPointVectorRepository();

    ParticipantGravityPointAction action(person,gravityPoints,pgpat_config);

    person->type = Person::PersonType::Bystander;

    Action* followup = nullptr;
    ASSERT_TRUE(action.isDone(followup));

    ASSERT_FALSE(followup);
}
