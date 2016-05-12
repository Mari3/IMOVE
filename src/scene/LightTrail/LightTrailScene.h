//
// Created by Wouter Posdijk on 11/05/16.
//

#ifndef IMOVE_LIGHTTRAILSCENE_H
#define IMOVE_LIGHTTRAILSCENE_H


#include "../Scene.h"
#include "LightSource.h"
#include "GravityPoint.h"
#include "ColorHole.h"

class LightTrailScene : public Scene{
private:
    vector<LightSource*> lightSources;
    vector<LightTrail*> lightTrails;
    vector<GravityPoint*> gravityPoints;
    vector<ColorHole*> colorHoles;
public:
    LightTrailScene();
    virtual void draw(sf::RenderTarget &target) override;
};


#endif //IMOVE_LIGHTTRAILSCENE_H
