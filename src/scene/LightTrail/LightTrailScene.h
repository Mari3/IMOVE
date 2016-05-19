//
// Created by Wouter Posdijk on 11/05/16.
//

#ifndef IMOVE_LIGHTTRAILSCENE_H
#define IMOVE_LIGHTTRAILSCENE_H


#include "../Scene.h"
#include "LightSource.h"
#include "GravityPoint.h"
#include "ColorHole.h"
#include "Repositories/LightSourceRepository.h"
#include "Repositories/LightTrailRepository.h"
#include "Repositories/GravityPointRepository.h"
#include "Repositories/ColorHoleRepository.h"
#include "Repositories/LightPersonRepository.h"

class LightTrailScene : public Scene{
private:
    LightSourceRepository* lightSources;
    LightTrailRepository* lightTrails;
    GravityPointRepository* gravityPoints;
    ColorHoleRepository* colorHoles;
    LightPersonRepository* lightPeople;
    sf::RenderTexture texture;
public:
    LightTrailScene();
    virtual void draw(sf::RenderTarget &target) override;
    void updatePeople(vector<Person> newPeople) override;
};


#endif //IMOVE_LIGHTTRAILSCENE_H
