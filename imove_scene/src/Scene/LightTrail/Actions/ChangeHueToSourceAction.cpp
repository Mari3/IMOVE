//
// Created by Wouter Posdijk on 07/06/16.
//

#include <math.h>
#include "ChangeHueToSourceAction.h"
#include "../../../../../imove_peopleextractor/src/Person.h"

void ChangeHueToSourceAction::execute(float dt) {
    person->hue = sourceHue;
}

bool ChangeHueToSourceAction::isDone(std::vector<Action *> &followUp) {
    return true;
}

ChangeHueToSourceAction::ChangeHueToSourceAction(std::shared_ptr<LightPerson> person,
                                                 std::shared_ptr<LightSource> source) : person(person) {
    sourceHue = source->getHue();
}

