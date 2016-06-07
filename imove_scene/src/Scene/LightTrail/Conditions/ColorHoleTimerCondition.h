//
// Created by Wouter Posdijk on 06/06/16.
//

#ifndef IMOVE_COLORHOLETIMERCONDITION_H
#define IMOVE_COLORHOLETIMERCONDITION_H


#include "../Repositories/LightsSceneRepositories.h"
#include "../../Condition.h"

class ColorHoleTimerCondition : public Condition {
private:
    ColorHoleRepository* colorHoles;
    LightPersonRepository* lightPeople;
    LightTrailRepository* lightTrails;
    GravityPointRepository* gravityPoints;
    LightTrailConfiguration config;
    Timer timer;
public:
    ColorHoleTimerCondition(ColorHoleRepository *colorHoles,
                                LightPersonRepository *lightPeople,
                                const LightTrailConfiguration &config,
                                LightTrailRepository *lightTrails,
                                GravityPointRepository *gravityPoints);

    int check(float dt, std::vector<Action *> &actions) override;


};


#endif //IMOVE_COLORHOLETIMERCONDITION_H
