//
// Created by Wouter Posdijk on 26/05/16.
//

#include <gtest/gtest.h>
#include <fakeit.hpp>
#include "../../../../../src/Scene/LightTrail/Configuration/LightTrailConfiguration.h"
#include "../../../../../src/Scene/LightTrail/Repositories/LightsSceneRepositories.h"
#include "../../../../../src/Scene/LightTrail/Repositories/LightsSceneVectorRepositories.h"
#include "../../../../../src/Scene/LightTrail/Actions/UpdateLightSourcesAction.h"
#include "../../../../../src/Scene/Util/Range.h"
#include "../../../../../../scene_interface/src/Vector2.h"

using namespace fakeit;

<<<<<<< e14e2fad4a34a757ed2f93aabb12006ddb542b15
LightTrailConfiguration config_ulsat(800, 600, util::Range(0, 0), util::Range(0, 0), util::Range(0, 0),
                                     util::Range(0, 0), 2.f, 10, util::Range(0, 100),
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
<<<<<<< a433a11f63b8a09e98546efa02c2aedebd785d20
                                     0, 0, 0);
=======
                                     0, 0, 0,
                                     0);
>>>>>>> Add configuration for star effect
=======
LightTrailConfiguration config_ulsat(0, 0, util::Range(0, 0), util::Range(0, 0), util::Range(0, 0), util::Range(0, 0),
                                     0,
                                     0, util::Range(0, 0), 0, 0, 0, 0, 0,
                                     0, (StarConfig()));
>>>>>>> Refactor configuration from sig feedback

TEST (UpdateLightSourceTest, LightTrailMadeAfterTime) {

    LightTrailRepository* trails = new LightTrailVectorRepository();

    LightSourceRepository* sources = new LightSourceVectorRepository();
    sources->add(std::shared_ptr<LightSource>(
            new LightSource(Vector2(0, 0), util::Range(0, 0, true), util::Range(0, 0, true),
                            util::Range(0, 0, true), 0)));

    UpdateLightSourcesAction action(sources,trails,config_ulsat);

    ASSERT_EQ(trails->size(),0);

    action.execute(1.9f);

    ASSERT_EQ(trails->size(),0);

    action.execute(.100001f);

    ASSERT_EQ(trails->size(),1);
}

TEST (UpdateLightSourceTest, StayWithinCap) {
    LightTrailRepository* trails = new LightTrailVectorRepository();
    for(int i=0;i<10;++i){
        trails->add(std::shared_ptr<LightTrail>(new LightTrail(Vector2(0,0),Vector2(0,0),0)));
    }

    LightSourceRepository* sources = new LightSourceVectorRepository();
    sources->add(std::shared_ptr<LightSource>(
            new LightSource(Vector2(0, 0), util::Range(0, 0, true), util::Range(0, 0, true),
                            util::Range(0, 0, true), 0)));

    UpdateLightSourcesAction action(sources,trails,config_ulsat);

    ASSERT_EQ(trails->size(),10);

    action.execute(2.1f);

    ASSERT_EQ(trails->size(),10);
}
