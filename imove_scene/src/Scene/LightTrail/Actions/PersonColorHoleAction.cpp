//
// Created by Wouter Posdijk on 06/06/16.
//

#include "PersonColorHoleAction.h"

PersonColorHoleAction::PersonColorHoleAction(const shared_ptr<LightPerson> &person,
                                             GravityPointRepository *gravityPoints, ColorHoleRepository *colorHoles,
                                             LightTrailRepository *lightTrails, LightPersonRepository *lightPeople)
        : person(person),
          gravityPoints(
                  gravityPoints),
          colorHoles(colorHoles),
          lightTrails(
                  lightTrails), lightPeople(lightPeople) {
    util::Range hue = person->hue;
    hue += 180.f;
    ColorHole* hole = new ColorHole(person->getLocation(),hue,1000000,300);
    colorHole = std::shared_ptr<ColorHole>(hole);
    colorHoles->add(colorHole);
    gravityPoints->add(colorHole);
}

bool PersonColorHoleAction::isDone(std::vector<Action *> &followUp) {
    if(person->type == None){
        finish();
        return true;
    }
    bool done = false;
    lightPeople->for_each([&](std::shared_ptr<LightPerson> person){
        if(!done && person != this->person) {
            float diff = (person->getLocation() - colorHole->location).size();
            if (diff < 30.f) {
                finish();
                //TODO create followup
                done = true;
            }
        }
    });
    return done;
}

void PersonColorHoleAction::execute(float dt) {
    colorHole->location.x = person->getLocation().x;
    colorHole->location.y = person->getLocation().y;
    lightTrails->for_each([&](std::shared_ptr<LightTrail> trail){
        float diff = (trail->getLocation()-colorHole->location).size();
        if(diff < 30.f && colorHole->hue.contains(trail->hue)){
            colorHole->consume(trail);
            lightTrails->scheduleForRemoval(trail);
        }
    });
}

void PersonColorHoleAction::finish() {
    vector<std::shared_ptr<LightTrail>> trails = colorHole->explode();
    for (auto &trail : trails) {
        lightTrails->add(trail);
    }
    gravityPoints->scheduleForRemoval(colorHole);
    colorHoles->scheduleForRemoval(colorHole);
}

