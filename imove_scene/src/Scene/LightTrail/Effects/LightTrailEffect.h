//
// Created by Wouter Posdijk on 10/06/16.
//

#ifndef IMOVE_LIGHTTRAILEFFECT_H
#define IMOVE_LIGHTTRAILEFFECT_H


#include "Effect.h"
#include "../Repositories/LightsSceneRepositories.h"

// Draws light trails on a texture
class LightTrailEffect : public Effect {
private:
    LightTrailRepository *trails;
    LightTrailSceneConfiguration config;
    sf::RenderTexture &texture;
public:

    LightTrailEffect(LightTrailRepository *trails, const LightTrailSceneConfiguration &config,
                         sf::RenderTexture &texture);

    void update(float dt) override;

    void draw(sf::RenderTarget &target) override;


};


#endif //IMOVE_LIGHTTRAILEFFECT_H
