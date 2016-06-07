//
// Created by Wouter Posdijk on 18/05/16.
//

#ifndef IMOVE_DELETEALLACTION_H
#define IMOVE_DELETEALLACTION_H


#include "../../Action.h"
#include "../Repositories/LightPersonMapRepository.h"
#include "../Repositories/LightsSceneRepositories.h"

using namespace scene_interface;

class DeleteAllAction : public Action {
private:
    ColorHoleRepository* colorHoles;
    GravityPointRepository* gravityPoints;
    LightPersonRepository* lightPeople;
    LightSourceRepository* lightSources;
    LightTrailRepository* lightTrails;
public:
    DeleteAllAction(ColorHoleRepository *colorHoles, GravityPointRepository *gravityPoints,
                    LightPersonRepository *lightPeople, LightSourceRepository *lightSources,
                    LightTrailRepository *lightTrails);

    bool isDone(std::vector<Action*> &followUp) override;

    void execute(float dt) override;


};


#endif //IMOVE_DELETEALLACTION_H
