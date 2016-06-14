//
// Created by Wouter Posdijk on 24/05/16.
//

#ifndef IMOVE_LIGHTTRAILCONFIGURATION_H
#define IMOVE_LIGHTTRAILCONFIGURATION_H

#include <cstdint>
#include <string>
#include <vector>
#include "../../Util/Range.h"
#include "TrailConfiguration.h"
#include "GravityConfiguration.h"
#include "EffectConfiguration.h"


class LightTrailSceneConfiguration {
private:
    // Screen size
    unsigned int _screenWidth, _screenHeight;
    TrailConfiguration _trailConfiguration;
    GravityConfiguration _gravityConfiguration;
    EffectConfiguration _effectConfiguration;


public:


    LightTrailSceneConfiguration(unsigned int _screenWidth, unsigned int _screenHeight,
                                 const TrailConfiguration &_trailConfiguration,
                                 const GravityConfiguration &_gravityConfiguration,
                                 const EffectConfiguration &_effectConfiguration);

    static LightTrailSceneConfiguration readFromFile(char* fileName);


    unsigned int screenWidth() const;

    unsigned int screenHeight() const;

    const TrailConfiguration & trail() const;

    const GravityConfiguration & gravity() const;

    const EffectConfiguration & effect() const;
};


#endif //IMOVE_LIGHTTRAILCONFIGURATION_H
