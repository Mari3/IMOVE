//
// Created by Wouter Posdijk on 27/05/16.
//

#include <gtest/gtest.h>
<<<<<<< 06aee995ed42b7f05c320c1bec41f7877dc357ba
#include <vector>
#include "../../../../../src/Scene/LightTrail/Configuration/LightTrailConfiguration.h"
=======
#include "../../../../../src/Scene/LightTrail/Configuration/LightTrailSceneConfiguration.h"
>>>>>>> Refactor configuration
#include "../../../../../src/Scene/LightTrail/Repositories/LightPersonMapRepository.h"
#include "../../../../../src/Scene/LightTrail/Repositories/LightsSceneRepositories.h"
#include "../../../../../src/Scene/LightTrail/Repositories/LightsSceneVectorRepositories.h"
#include "../../../../../src/Scene/LightTrail/Conditions/PersonChangedTypeCondition.h"
#include "../../../../../src/Scene/LightTrail/Actions/BystanderGravityPointAction.h"
#include "../../../../../src/Scene/LightTrail/Actions/ParticipantGravityPointAction.h"
#include "../../../../../../imove_imp/src/Vector2.h"
#include "../../../../../../scene_interface/src/Person.h"

<<<<<<< 06aee995ed42b7f05c320c1bec41f7877dc357ba
LightTrailConfiguration config_pctc(0, 0, std::vector<util::Range>(), LightSourceConfig(), ParticipantGravityConfig(),
        DelayGravityConfig(), DelayGravityConfig(), ProximityConfig(), false, TrailConfig(),
0, MixingConfig(), ExplosionConfig(), GravityConfig(), ColorHoleConfig(),
        StarConfig(), 0);
=======
LightTrailSceneConfiguration config_pctc(0, 0, util::Range(0, 0), util::Range(0, 0), util::Range(0, 0), util::Range(0, 0), 0,
                                    0, util::Range(0, 0), 0, 0, 0, 0, 0,
                                    0, (StarConfig()), 0);
>>>>>>> Refactor configuration

TEST(PersonChangedTypeConditionTest, BystanderTurnedParticipant) {

    LightPersonRepository* lightPeople = new LightPersonMapRepository();
    GravityPointRepository* gravityPoints = new GravityPointVectorRepository();

    std::shared_ptr<LightPerson> person(new LightPerson(Location(0,0),0,Person::PersonType::Bystander,util::Range(0,180,true)));
    lightPeople->add(person);

    PersonChangedTypeCondition condition(lightPeople, gravityPoints, nullptr, nullptr, config_pctc, <#initializer#>);

    std::vector<Action*> actions;
    condition.check(0,actions);

    ASSERT_EQ(actions.size(),1);

    ASSERT_TRUE(dynamic_cast<BystanderGravityPointAction*>(actions[0]));

    actions.clear();
    condition.check(0,actions);

    ASSERT_EQ(actions.size(),0);

    person->type = Person::PersonType::Participant;

    actions.clear();
    condition.check(0,actions);

    ASSERT_EQ(actions.size(),1);
    ASSERT_TRUE(dynamic_cast<ParticipantGravityPointAction*>(actions[0]));

}

TEST(PersonChangedTypeConditionTest, ParticipantTurnedBystander) {

    LightPersonRepository* lightPeople = new LightPersonMapRepository();
    GravityPointRepository* gravityPoints = new GravityPointVectorRepository();

    std::shared_ptr<LightPerson> person(new LightPerson(Location(0,0),0,Person::PersonType::Participant,util::Range(0,180,true)));
    lightPeople->add(person);

    PersonChangedTypeCondition condition(lightPeople, gravityPoints, nullptr, nullptr, config_pctc, <#initializer#>);

    std::vector<Action*> actions;
    condition.check(0,actions);

    ASSERT_EQ(actions.size(),1);

    ASSERT_TRUE(dynamic_cast<ParticipantGravityPointAction*>(actions[0]));

    actions.clear();
    condition.check(0,actions);

    ASSERT_EQ(actions.size(),0);

    person->type = Person::PersonType::Bystander;

    actions.clear();
    condition.check(0,actions);

    ASSERT_EQ(actions.size(),1);
    ASSERT_TRUE(dynamic_cast<BystanderGravityPointAction*>(actions[0]));

}

TEST(PersonChangedTypeConditionTest, TwoPeople) {
    LightPersonRepository* lightPeople = new LightPersonMapRepository();
    GravityPointRepository* gravityPoints = new GravityPointVectorRepository();

    std::shared_ptr<LightPerson> person1(new LightPerson(Location(0,0),0,Person::PersonType::Participant,util::Range(0,180,true)));
    std::shared_ptr<LightPerson> person2(new LightPerson(Location(0,0),1,Person::PersonType::Bystander,util::Range(0,180,true)));
    lightPeople->add(person1);
    lightPeople->add(person2);

    PersonChangedTypeCondition condition(lightPeople, gravityPoints, nullptr, nullptr, config_pctc, <#initializer#>);

    std::vector<Action*> actions;
    condition.check(0,actions);

    ASSERT_EQ(actions.size(),2);

    BystanderGravityPointAction* bAction = dynamic_cast<BystanderGravityPointAction*>(actions[0]);
    ParticipantGravityPointAction* pAction;
    if(!bAction){
        bAction = dynamic_cast<BystanderGravityPointAction*>(actions[1]);
        pAction = dynamic_cast<ParticipantGravityPointAction*>(actions[0]);
    }else{
        pAction = dynamic_cast<ParticipantGravityPointAction*>(actions[1]);
    }
    ASSERT_TRUE(bAction);
    ASSERT_TRUE(pAction);

    actions.clear();
    condition.check(0,actions);

    ASSERT_EQ(actions.size(),0);

    person1->type = Person::PersonType::Bystander;

    actions.clear();
    condition.check(0,actions);

    ASSERT_EQ(actions.size(),1);
    ASSERT_TRUE(dynamic_cast<BystanderGravityPointAction*>(actions[0]));
}
