//
// Created by Wouter Posdijk on 06/06/16.
//

#include <cstdlib>
#include "ColorHoleTimerCondition.h"
#include "../Actions/PersonColorHoleAction.h"

ColorHoleTimerCondition::ColorHoleTimerCondition(
	 ColorHoleRepository *colorHoles,
	 LightPersonRepository *lightPeople,
	 const LightTrailConfiguration &config,
	 LightTrailRepository *lightTrails,
	 GravityPointRepository *gravityPoints
) :
	colorHoles(colorHoles),
	lightPeople(lightPeople),
    lightTrails(lightTrails),
    gravityPoints(gravityPoints),
    config(config),
    timer(10.f)
{ }

int ColorHoleTimerCondition::check(float dt, std::vector<Action *> &actions) {
    if(lightPeople->size() > 0 && colorHoles->size() == 0 && timer.update(dt)) {
        //Pick the next person to get a color hole
        int index = rand() % static_cast<int>(lightPeople->size());
        int j = 0;
        lightPeople->for_each([&](std::shared_ptr<LightPerson> person) {
            if (j == index) {
                timer.restart();
                Action *action = new PersonColorHoleAction(person, gravityPoints, colorHoles, lightTrails, lightPeople,
                                                           config);
                actions.push_back(action);
            }
            j++;
        });
        return 1;
    }
    return 0;
}
