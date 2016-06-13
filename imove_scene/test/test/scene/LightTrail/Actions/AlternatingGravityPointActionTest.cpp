//
// Created by Wouter Posdijk on 27/05/16.
//

#include <gtest/gtest.h>
#include <vector>
#include <fakeit.hpp>
#include "../../../../../src/Scene/LightTrail/Configuration/LightTrailSceneConfiguration.h"
#include "../../../../../src/Scene/LightTrail/Repositories/LightsSceneRepositories.h"
#include "../../../../../src/Scene/LightTrail/Repositories/LightsSceneVectorRepositories.h"
#include "../../../../../src/Scene/LightTrail/Actions/AlternatingGravityPointAction.h"

using namespace fakeit;

<<<<<<< 06aee995ed42b7f05c320c1bec41f7877dc357ba
LightTrailConfiguration agpat_config(0, 0, std::vector<util::Range>(), LightSourceConfig(), ParticipantGravityConfig(),
                                   DelayGravityConfig(), DelayGravityConfig(), ProximityConfig(), false, TrailConfig(),
                                   0, MixingConfig(), ExplosionConfig(), GravityConfig(), ColorHoleConfig(),
                                   StarConfig(), 0);

=======
LightTrailSceneConfiguration agpat_config(0, 0, util::Range(0, 0), util::Range(0, 0), util::Range(0, 0), util::Range(0, 0),
                                     0,
                                     0, util::Range(0, 0), 0, 0, 0, 0, 0,
                                     0, (StarConfig()), 0);
>>>>>>> Refactor configuration

TEST (AlternatingGravityPointActionTest, UpdateLocation) {

    GravityPointRepository* gravityPoints = new GravityPointVectorRepository();
    LightPersonRepository* lightPeople = new LightPersonMapRepository();

    Mock<RangeRandom> xRandom;
    Mock<RangeRandom> yRandom;

    When(Method(xRandom,next)).Return(20,45);
    When(Method(yRandom,next)).Return(40,89);

    util::Range xRange(0,0,&xRandom.get());
    util::Range yRange(0,0,&yRandom.get());

    AlternatingGravityPointAction action(util::Range(0, 180), xRange,
                                         yRange, gravityPoints, lightPeople, nullptr, agpat_config);

    ASSERT_EQ(gravityPoints->size(),1);

    std::shared_ptr<GravityPoint> gPoint = gravityPoints->get(0);

    ASSERT_FLOAT_EQ(gPoint->location.x,20);
    ASSERT_FLOAT_EQ(gPoint->location.y,40);

    action.execute(3.f);

    ASSERT_FLOAT_EQ(gPoint->location.x,20);
    ASSERT_FLOAT_EQ(gPoint->location.y,40);

    action.execute(3.f);

    ASSERT_FLOAT_EQ(gPoint->location.x,45);
    ASSERT_FLOAT_EQ(gPoint->location.y,89);

}
