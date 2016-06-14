#ifndef IMOVE_LIGHTTRAILSCENE_H
#define IMOVE_LIGHTTRAILSCENE_H


#include "../Scene.h"
#include "LightSource.h"
#include "GravityPoint.h"
#include "ColorHole.h"
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
    std::vector<LightTrailRepository*> sourceTrails;
    LightTrailConfiguration config;
    sf::RenderTexture texture;
    int hueCounter;
public:
    LightTrailScene(const LightTrailConfiguration &config,
                    LightSourceRepository* lightSources, LightTrailRepository* lightTrails,
                    GravityPointRepository* gravityPoints, ColorHoleRepository* colorHoles,
                    LightPersonRepository* lightPeople);
    void draw(sf::RenderTarget &target) override;
    void processPeople() override;
};


#endif //IMOVE_LIGHTTRAILSCENE_H
