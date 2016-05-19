//
// Created by Wouter Posdijk on 17/05/16.
//

#ifndef IMOVE_LIGHTTRAILREPOSITORY_H
#define IMOVE_LIGHTTRAILREPOSITORY_H


#include "../LightTrail.h"
#include "../../../util/VectorRepository.h"

class LightTrailRepository : public VectorRepository<LightTrail> {
private:
    static LightTrailRepository* _instance;
    LightTrailRepository(){}
public:
    static LightTrailRepository * getInstance();
};


#endif //IMOVE_LIGHTTRAILREPOSITORY_H
