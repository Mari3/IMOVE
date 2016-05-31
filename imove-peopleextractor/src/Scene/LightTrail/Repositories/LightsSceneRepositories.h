//
// Created by Wouter Posdijk on 24/05/16.
//

#ifndef IMOVE_LIGHTSSCENEREPOSITORIES_H
#define IMOVE_LIGHTSSCENEREPOSITORIES_H

#include "../ColorHole.h"
#include "../../Util/Repository.h"
#include "../LightPerson.h"
#include "../LightSource.h"

typedef Repository<ColorHole> ColorHoleRepository;
typedef Repository<GravityPoint> GravityPointRepository;
typedef Repository<LightPerson> LightPersonRepository;
typedef Repository<LightSource> LightSourceRepository;
typedef Repository<LightTrail> LightTrailRepository;

#endif //IMOVE_LIGHTSSCENEREPOSITORIES_H
