//
// Created by Wouter Posdijk on 25/05/16.
//

#ifndef IMOVE_LIGHTSSCENEVECTORREPOSITORIES_H
#define IMOVE_LIGHTSSCENEVECTORREPOSITORIES_H

#include "../ColorHole.h"
#include "../../../util/VectorRepository.h"
#include "../LightSource.h"

typedef VectorRepository<ColorHole> ColorHoleVectorRepository;
typedef VectorRepository<GravityPoint> GravityPointVectorRepository;
typedef VectorRepository<LightSource> LightSourceVectorRepository;
typedef VectorRepository<LightTrail> LightTrailVectorRepository;

#endif //IMOVE_LIGHTSSCENEVECTORREPOSITORIES_H
