//
// Created by Wouter Posdijk on 26/05/16.
//


#include <gtest/gtest.h>
#include "../../../../../src/scene/LightTrail/LightTrailConfiguration.h"
#include "../../../../../src/scene/LightTrail/Repositories/LightsSceneVectorRepositories.h"
#include "../../../../../src/scene/LightTrail/Repositories/LightsSceneRepositories.h"
#include "../../../../../src/scene/LightTrail/Actions/UpdateLightTrailsAction.h"

LightTrailConfiguration config2(800, 600, util::Range(0, 0), util::Range(0, 0), util::Range(0, 0), util::Range(0, 0),
                               2.f,10,util::Range(0,400),0,0,0,0,0,400,.5,true,200,0,0);

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