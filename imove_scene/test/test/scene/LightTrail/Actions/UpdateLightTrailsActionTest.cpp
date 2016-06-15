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
#include "../../../../../src/Scene/LightTrail/Repositories/LightsSceneVectorRepositories.h"
#include "../../../../../src/Scene/LightTrail/Repositories/LightsSceneRepositories.h"
#include "../../../../../src/Scene/LightTrail/Actions/UpdateLightTrailsAction.h"
#include "../../../../../../imove_imp/src/Vector2.h"

<<<<<<< 06aee995ed42b7f05c320c1bec41f7877dc357ba
LightTrailConfiguration config2(0, 0, std::vector<util::Range>(), LightSourceConfig(), ParticipantGravityConfig(),
        DelayGravityConfig(), DelayGravityConfig(), ProximityConfig(), false, TrailConfig(),
0, MixingConfig(), ExplosionConfig(), GravityConfig(), ColorHoleConfig(),
        StarConfig(), 0);
=======
LightTrailSceneConfiguration config2(0, 0, util::Range(0, 0), util::Range(0, 0), util::Range(0, 0), util::Range(0, 0), 0,
                                0, util::Range(0, 0), 0, 0, 0, 0, 0,
                                0, (StarConfig()), 0);
>>>>>>> Refactor configuration

TEST (UpdateLightTrailsActionTest, OutsideProximityRange) {

    LightTrailRepository* trails = new LightTrailVectorRepository();
    GravityPointRepository* gravityPoints = new GravityPointVectorRepository();

    std::shared_ptr<LightTrail> trail(new LightTrail(Vector2(300,300),Vector2(0,0),0));
    trails->add(trail);

    gravityPoints->add(std::shared_ptr<GravityPoint>(new GravityPoint(Vector2(600,700),util::Range(0,0),20000)));

    UpdateLightTrailsAction action(trails,gravityPoints,config2);

    action.execute(.1);
    ASSERT_FLOAT_EQ(trail->getSpeed().x,2.4);
    ASSERT_FLOAT_EQ(trail->getSpeed().y,3.2);

    ASSERT_FLOAT_EQ(trail->getLocation().x,300.24);
    ASSERT_FLOAT_EQ(trail->getLocation().y,300.32);
}

// No Tests for inside proximity range, since this behaviour is still undefined
