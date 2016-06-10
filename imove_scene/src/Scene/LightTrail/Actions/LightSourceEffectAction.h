//
// Created by Wouter Posdijk on 31/05/16.
//

#ifndef IMOVE_LIGHTSOURCEEFFECTACTION_H
#define IMOVE_LIGHTSOURCEEFFECTACTION_H


#include "../../Action.h"
#include "../GravityPoint.h"
#include "../Repositories/LightsSceneRepositories.h"
#include "../Effects/LightTrailEffect.h"

class LightSourceEffectAction : public Action {
private:
    GravityPoint gravityPoint;
    LightTrailRepository* myLightTrails;
    LightTrailConfiguration config;
    LightTrailEffect effect;
public:
    LightSourceEffectAction(std::shared_ptr<LightSource> source, LightTrailRepository *myLightTrails,
                            const LightTrailConfiguration& config, sf::RenderTexture &texture
    );

    bool isDone(std::vector<Action *> &followUp) override;

    void execute(float dt) override;

    void draw(sf::RenderTarget &target) override;


};


#endif //IMOVE_LIGHTSOURCEEFFECTACTION_H
