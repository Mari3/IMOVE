//
// Created by Wouter Posdijk on 31/05/16.
//

#ifndef IMOVE_LIGHTSOURCEEFFECTACTION_H
#define IMOVE_LIGHTSOURCEEFFECTACTION_H


#include "../../Action.h"
#include "../GravityPoint.h"
#include "../Repositories/LightsSceneRepositories.h"
#include "../Effects/LightTrailEffect.h"

// Creates the effect of light trails bouncing around
// a light source
class LightSourceEffectAction : public Action {
private:
    GravityPoint gravityPoint;
    LightTrailRepository* myLightTrails;
    LightTrailSceneConfiguration config;
public:
    LightSourceEffectAction(std::shared_ptr<LightSource> source, LightTrailRepository *myLightTrails,
                            const LightTrailSceneConfiguration& config, sf::RenderTexture &texture
    );

    bool isDone(std::vector<Action *> &followUp) override;

    void execute(float dt) override;


};


#endif //IMOVE_LIGHTSOURCEEFFECTACTION_H
