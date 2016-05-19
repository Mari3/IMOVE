//
// Created by Wouter Posdijk on 18/05/16.
//

#ifndef IMOVE_DELETEALLACTION_H
#define IMOVE_DELETEALLACTION_H


#include "../../Action.h"
#include "../Repositories/ColorHoleRepository.h"
#include "../Repositories/GravityPointRepository.h"
#include "../Repositories/LightPersonRepository.h"
#include "../Repositories/LightSourceRepository.h"
#include "../Repositories/LightTrailRepository.h"

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
