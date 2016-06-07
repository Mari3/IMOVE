//
// Created by Wouter Posdijk on 07/06/16.
//

#include <math.h>
#include "ChangeHueToSourceAction.h"

void ChangeHueToSourceAction::execute(float dt) {
    float progress = progressLeft < 0 ? -45*dt : 45*dt;
    if(fabsf(progressLeft) < fabsf(progress)){
        progress = progressLeft;
    }
    person->hue += progress;
    progressLeft -= progress;
}

bool ChangeHueToSourceAction::isDone(std::vector<Action *> &followUp) {
    return fabsf(progressLeft) < 0.001 || person->type == None || person->type == Bystander;
}

ChangeHueToSourceAction::ChangeHueToSourceAction(std::shared_ptr<LightPerson> person,
                                                 std::shared_ptr<LightSource> source) : person(person) {
    float huediff = person->hue.getCenter()-source->getHue().getCenter();
    if(huediff > 180) huediff-=360;
    progressLeft = huediff;
}

