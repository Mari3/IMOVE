//
// Created by Wouter Posdijk on 31/05/16.
//

#ifndef IMOVE_LIGHTSOURCEEFFECTACTION_H
#define IMOVE_LIGHTSOURCEEFFECTACTION_H


#include "../../Action.h"
#include "../GravityPoint.h"
#include "../Repositories/LightsSceneRepositories.h"

class LightSourceEffectAction : public Action {
private:
    GravityPoint gravityPoint;
    LightTrailRepository* myLightTrails;
    LightTrailConfiguration config;
public:
    LightSourceEffectAction(shared_ptr<LightSource> source, LightTrailRepository *myLightTrails,
                            const LightTrailConfiguration& config
    );

    bool isDone(std::vector<Action *> &followUp);

    void execute(float dt);


};


#endif //IMOVE_LIGHTSOURCEEFFECTACTION_H
