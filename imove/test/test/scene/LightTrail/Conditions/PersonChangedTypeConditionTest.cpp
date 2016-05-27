//
// Created by Wouter Posdijk on 27/05/16.
//

#include <gtest/gtest.h>
#include "../../../../../src/scene/LightTrail/LightTrailConfiguration.h"
#include "../../../../../src/scene/LightTrail/Repositories/LightPersonMapRepository.h"
#include "../../../../../src/scene/LightTrail/Repositories/LightsSceneRepositories.h"
#include "../../../../../src/scene/LightTrail/Repositories/LightsSceneVectorRepositories.h"
#include "../../../../../src/scene/LightTrail/Conditions/PersonChangedTypeCondition.h"
#include "../../../../../src/scene/LightTrail/Actions/BystanderGravityPointAction.h"
#include "../../../../../src/scene/LightTrail/Actions/ParticipantGravityPointAction.h"

LightTrailConfiguration config_pctc(800, 600, util::Range(0, 0), util::Range(0, 0), util::Range(0, 0), util::Range(0, 0),
                                    2.f, 10, util::Range(0,400), 0, 0, 0, 0, 0, 0, 400, .5, true, 200, 0, 0);

TEST(PersonChangedTypeConditionTest, BystanderTurnedParticipant) {

    LightPersonRepository* lightPeople = new LightPersonMapRepository();
    GravityPointRepository* gravityPoints = new GravityPointVectorRepository();

    shared_ptr<LightPerson> person(new LightPerson(Vector2(0,0),0,Bystander,util::Range(0,180,true)));
    lightPeople->add(person);

    PersonChangedTypeCondition condition(lightPeople,gravityPoints,config_pctc);

    std::vector<Action*> actions;
    condition.check(0,actions);

    ASSERT_EQ(actions.size(),1);

    ASSERT_TRUE(dynamic_cast<BystanderGravityPointAction*>(actions[0]));

    actions.clear();
    condition.check(0,actions);

    ASSERT_EQ(actions.size(),0);

    person->type = Participant;

    actions.clear();
    condition.check(0,actions);

    ASSERT_EQ(actions.size(),1);
    ASSERT_TRUE(dynamic_cast<ParticipantGravityPointAction*>(actions[0]));

}

TEST(PersonChangedTypeConditionTest, ParticipantTurnedBystander) {

    LightPersonRepository* lightPeople = new LightPersonMapRepository();
    GravityPointRepository* gravityPoints = new GravityPointVectorRepository();

    shared_ptr<LightPerson> person(new LightPerson(Vector2(0,0),0,Participant,util::Range(0,180,true)));
    lightPeople->add(person);

    PersonChangedTypeCondition condition(lightPeople,gravityPoints,config_pctc);

    std::vector<Action*> actions;
    condition.check(0,actions);

    ASSERT_EQ(actions.size(),1);

    ASSERT_TRUE(dynamic_cast<ParticipantGravityPointAction*>(actions[0]));

    actions.clear();
    condition.check(0,actions);

    ASSERT_EQ(actions.size(),0);

    person->type = Bystander;

    actions.clear();
    condition.check(0,actions);

    ASSERT_EQ(actions.size(),1);
    ASSERT_TRUE(dynamic_cast<BystanderGravityPointAction*>(actions[0]));

}

TEST(PersonChangedTypeConditionTest, TwoPeople) {
    LightPersonRepository* lightPeople = new LightPersonMapRepository();
    GravityPointRepository* gravityPoints = new GravityPointVectorRepository();

    shared_ptr<LightPerson> person1(new LightPerson(Vector2(0,0),0,Participant,util::Range(0,180,true)));
    shared_ptr<LightPerson> person2(new LightPerson(Vector2(0,0),1,Bystander,util::Range(0,180,true)));
    lightPeople->add(person1);
    lightPeople->add(person2);

    PersonChangedTypeCondition condition(lightPeople,gravityPoints,config_pctc);

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

    person1->type = Bystander;

    actions.clear();
    condition.check(0,actions);

    ASSERT_EQ(actions.size(),1);
    ASSERT_TRUE(dynamic_cast<BystanderGravityPointAction*>(actions[0]));
}