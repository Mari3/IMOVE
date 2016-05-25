//
// Created by Wouter Posdijk on 11/05/16.
//

#ifndef IMOVE_LIGHTTRAILSCENE_H
#define IMOVE_LIGHTTRAILSCENE_H


#include "../Scene.h"
#include "LightSource.h"
#include "GravityPoint.h"
#include "ColorHole.h"
#include "Repositories/LightSourceVectorRepository.h"
#include "Repositories/LightTrailVectorRepository.h"
#include "Repositories/GravityPointVectorRepository.h"
#include "Repositories/ColorHoleVectorRepository.h"
#include "Repositories/LightPersonMapRepository.h"
#include "Repositories/LightsSceneRepositories.h"
#include "LightTrailConfiguration.h"

class LightTrailScene : public Scene{
private:
    LightSourceRepository* lightSources;
    LightTrailRepository* lightTrails;
    GravityPointRepository* gravityPoints;
    ColorHoleRepository* colorHoles;
    LightPersonRepository* lightPeople;
    LightTrailConfiguration config;
    sf::RenderTexture texture;
public:
    LightTrailScene(LightTrailConfiguration config);
    void draw(sf::RenderTarget &target) override;
    void processPeople() override;
};


#endif //IMOVE_LIGHTTRAILSCENE_H
