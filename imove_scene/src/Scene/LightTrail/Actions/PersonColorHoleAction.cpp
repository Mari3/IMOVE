//
// Created by Wouter Posdijk on 06/06/16.
//

#include "PersonColorHoleAction.h"

PersonColorHoleAction::PersonColorHoleAction(const std::shared_ptr<LightPerson> &person,
                                             GravityPointRepository *gravityPoints, ColorHoleRepository *colorHoles,
                                             LightTrailRepository *lightTrails, LightPersonRepository *lightPeople,
                                             LightTrailConfiguration config)
        : person(person),
          gravityPoints(
                  gravityPoints),
          colorHoles(colorHoles),
          lightTrails(
                  lightTrails), lightPeople(lightPeople), config(config) {
    ColorHole* hole = new ColorHole(person->getLocation(),person->hue,config.colorHoleGravity(),config.colorHoleGravityRange());
    colorHole = std::shared_ptr<ColorHole>(hole);
    colorHoles->add(colorHole);
    gravityPoints->add(colorHole);
    person->isColorHole = true;
}

bool PersonColorHoleAction::isDone(std::vector<Action *> &followUp) {
    if(person->person_type == scene_interface::Person::PersonType::None){
        finish();
        return true;
    }
    bool done = false;
    lightPeople->for_each([&](std::shared_ptr<LightPerson> person){
        if(!done && person != this->person) {
            float diff = (person->getLocation() - colorHole->location).size();
            if (diff < config.colorHoleRange()) {
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
        if(diff < config.colorHoleRange() && colorHole->hue.contains(trail->hue)){
            colorHole->consume(trail);
            lightTrails->scheduleForRemoval(trail);
        }
    });
}

void PersonColorHoleAction::finish() {
    std::vector<std::shared_ptr<LightTrail>> trails = colorHole->explode();
    for (auto &trail : trails) {
        lightTrails->add(trail);
    }
    gravityPoints->scheduleForRemoval(colorHole);
    colorHoles->scheduleForRemoval(colorHole);
    person->isColorHole = false;
}

