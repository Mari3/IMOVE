//
// Created by Wouter Posdijk on 18/05/16.
//

#ifndef IMOVE_DELETEALLACTION_H
#define IMOVE_DELETEALLACTION_H


#include "../../Action.h"
#include "../Repositories/ColorHoleVectorRepository.h"
#include "../Repositories/GravityPointVectorRepository.h"
#include "../Repositories/LightPersonMapRepository.h"
#include "../Repositories/LightSourceVectorRepository.h"
#include "../Repositories/LightTrailVectorRepository.h"
#include "../Repositories/LightsSceneRepositories.h"

class DeleteAllAction : public Action {
private:
    ColorHoleRepository* colorHoles;
    GravityPointRepository* gravityPoints;
    LightPersonRepository* lightPeople;
    LightSourceRepository* lightSources;
    LightTrailRepository* lightTrails;
public:
    DeleteAllAction();

    bool isDone(Action *&followUp) override;

    void execute(float dt) override;


};


#endif //IMOVE_DELETEALLACTION_H
