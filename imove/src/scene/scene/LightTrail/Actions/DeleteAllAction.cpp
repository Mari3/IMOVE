//
// Created by Wouter Posdijk on 18/05/16.
//

#include "DeleteAllAction.h"

DeleteAllAction::DeleteAllAction() : colorHoles(ColorHoleRepository::getInstance()),
            gravityPoints(GravityPointRepository::getInstance()),
                                     lightPeople(LightPersonRepository::getInstance()),
                                     lightSources(LightSourceRepository::getInstance()),
                                     lightTrails(LightTrailRepository::getInstance())
{
}

bool DeleteAllAction::isDone(Action *&followUp) {
    return false;
}

void DeleteAllAction::execute(float dt) {
    colorHoles->removeAll();
    gravityPoints->removeAll();
    lightPeople->removeAll();
    lightSources->removeAll();
    lightTrails->removeAll();
}