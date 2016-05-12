//
// Created by Wouter Posdijk on 11/05/16.
//

#ifndef IMOVE_LIGHTTRAILSCENE_H
#define IMOVE_LIGHTTRAILSCENE_H


#include "../Scene.h"

class LightTrailScene : public Scene{
public:
    LightTrailScene();
    virtual void draw(sf::RenderTarget &target) override;
};


#endif //IMOVE_LIGHTTRAILSCENE_H
