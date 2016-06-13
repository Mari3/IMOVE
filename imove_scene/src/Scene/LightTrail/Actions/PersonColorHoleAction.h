//
// Created by Wouter Posdijk on 06/06/16.
//

#ifndef IMOVE_PERSONCOLORHOLEACTION_H
#define IMOVE_PERSONCOLORHOLEACTION_H


#include "../../Action.h"
#include "../LightPerson.h"
#include "../ColorHole.h"
#include "../Repositories/LightsSceneRepositories.h"
#include <vector>

class PersonColorHoleAction : public Action {
private:
    std::shared_ptr<LightPerson> person;
    std::shared_ptr<ColorHole> colorHole;
    GravityPointRepository* gravityPoints;
    ColorHoleRepository* colorHoles;
    LightTrailRepository* lightTrails;
    LightPersonRepository* lightPeople;
    LightTrailConfiguration config;
    void finish();
public:

    PersonColorHoleAction(const std::shared_ptr<LightPerson> &person,
                              GravityPointRepository *gravityPoints, ColorHoleRepository *colorHoles,
                              LightTrailRepository *lightTrails, LightPersonRepository *lightPeople,
                              LightTrailConfiguration config);

    bool isDone(std::vector<Action *> &followUp) override;

    void execute(float dt) override;


};


#endif //IMOVE_PERSONCOLORHOLEACTION_H
