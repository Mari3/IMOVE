//
// Created by Wouter Posdijk on 06/06/16.
//

#include "PersonColorHoleAction.h"

PersonColorHoleAction::PersonColorHoleAction(const std::shared_ptr<LightPerson> &person,
                                             GravityPointRepository *gravityPoints, ColorHoleRepository *colorHoles,
                                             LightTrailRepository *lightTrails, LightPersonRepository *lightPeople,
                                             LightTrailSceneConfiguration config)
        : person(person),
          gravityPoints(
                  gravityPoints),
          colorHoles(colorHoles),
          lightTrails(
                  lightTrails), lightPeople(lightPeople), config(config) {
    ColorHole* hole = new ColorHole(person->getLocation(),util::Range(0,360,true),config.effect().colorHole().gravity,config.effect().colorHole().range);
    colorHole = std::shared_ptr<ColorHole>(hole);
    colorHoles->add(colorHole);
    gravityPoints->add(colorHole);
    person->isColorHole = true;

    effects.push_back(std::unique_ptr<Effect>(
            static_cast<Effect*>(new ColorHoleEffect(person,config))
    ));
}

bool PersonColorHoleAction::isDone(std::vector<Action *> &followUp) {
    // If the person is not a participant anymore
    if(person->person_type != scene_interface::Person::PersonType::Participant){
        std::vector<std::shared_ptr<LightTrail>> trails = colorHole->explode();
        for (unsigned int i=10; i < trails.size(); ++i){
            std::shared_ptr<LightTrail> &trail = trails[i];
            lightTrails->add(trail);
        }
        finish();
        return true;
    }
    bool done = false;
    lightPeople->for_each([&](std::shared_ptr<LightPerson> person){
        if(!done && person != this->person) {
            float diff = (person->getLocation() - colorHole->location).size();
            // If the other person is close enough to this person
            if (diff < config.effect().colorHole().destructionRange) {
                finish();
                std::vector<std::shared_ptr<LightTrail>> trails = colorHole->explode();
                for (unsigned int i=0; i < trails.size(); ++i){
                    std::shared_ptr<LightTrail> &trail = trails[i];
                    lightTrails->add(trail);
                }
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
        // If a trail is close enough
        if(diff < config.effect().colorHole().consumeRange && colorHole->hue.contains(trail->hue)){
            // Consume it
            colorHole->consume(trail);
            lightTrails->scheduleForRemoval(trail);
        }
    });
}

void PersonColorHoleAction::finish() {
    gravityPoints->scheduleForRemoval(colorHole);
    colorHoles->scheduleForRemoval(colorHole);
    person->isColorHole = false;
}