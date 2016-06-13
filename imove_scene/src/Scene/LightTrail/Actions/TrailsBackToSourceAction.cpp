//
// Created by Wouter Posdijk on 02/06/16.
//

#include "TrailsBackToSourceAction.h"

bool TrailsBackToSourceAction::isDone(std::vector<Action *> &followUp) {
    int size = 0;
    lightPeople->for_each([&](std::shared_ptr<LightPerson> person){
        if(person->person_type == scene_interface::Person::PersonType::Participant || person->movement_type == scene_interface::Person::MovementType::StandingStill){
            ++size;
        }
    });

    if(size != 1){
        for(int i=0;i<3;++i){
            gravityPoints->scheduleForRemoval(gPoints[i]);
        }
        return true;
    }
    return false;

}

void TrailsBackToSourceAction::execute(float dt) {
    // This action does not actively do anything
}

TrailsBackToSourceAction::TrailsBackToSourceAction(GravityPointRepository *gravityPoints,
                                                   LightTrailConfiguration &config,
                                                   LightPersonRepository *lightPeople)
        : gravityPoints(gravityPoints), lightPeople(lightPeople) {
    gPoints[0] = std::shared_ptr<GravityPoint>(new GravityPoint(Vector2(config.screenWidth(),0),config.cornerHues()[1],200000));
    gPoints[1] = std::shared_ptr<GravityPoint>(new GravityPoint(Vector2(0,config.screenHeight()),config.cornerHues()[2],200000));
    gPoints[2] = std::shared_ptr<GravityPoint>(new GravityPoint(Vector2(config.screenWidth(),config.screenHeight()),config.cornerHues()[3],200000));

    for(int i=0;i<3;++i){
        gravityPoints->add(gPoints[i]);
    }
}
