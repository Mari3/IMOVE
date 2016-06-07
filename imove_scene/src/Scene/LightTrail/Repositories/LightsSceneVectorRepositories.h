//
// Created by Wouter Posdijk on 25/05/16.
//

#ifndef IMOVE_LIGHTSSCENEVECTORREPOSITORIES_H
#define IMOVE_LIGHTSSCENEVECTORREPOSITORIES_H

#include "../ColorHole.h"
#include "../../Util/VectorRepository.h"
#include "../LightSource.h"

using namespace scene_interface;

typedef VectorRepository<ColorHole> ColorHoleVectorRepository;
typedef VectorRepository<GravityPoint> GravityPointVectorRepository;
typedef VectorRepository<LightSource> LightSourceVectorRepository;
typedef VectorRepository<LightTrail> LightTrailVectorRepository;

#endif //IMOVE_LIGHTSSCENEVECTORREPOSITORIES_H
