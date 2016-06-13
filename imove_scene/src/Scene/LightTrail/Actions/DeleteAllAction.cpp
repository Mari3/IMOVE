//
// Created by Wouter Posdijk on 18/05/16.
//

#include "DeleteAllAction.h"

bool DeleteAllAction::isDone(std::vector<Action*> &followUp) {
    // This action is never done
    return false;
}

void DeleteAllAction::execute(float dt) {
    colorHoles->removeAll();
    gravityPoints->removeAll();
    lightPeople->removeAll();
    lightSources->removeAll();
    lightTrails->removeAll();
}

DeleteAllAction::DeleteAllAction(ColorHoleRepository *colorHoles, GravityPointRepository *gravityPoints,
                                 LightPersonRepository *lightPeople, LightSourceRepository *lightSources,
                                 LightTrailRepository *lightTrails)
        : colorHoles(colorHoles), gravityPoints(gravityPoints),
          lightPeople(lightPeople), lightSources(lightSources),
          lightTrails(lightTrails) { }