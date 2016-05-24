//
// Created by Wouter Posdijk on 17/05/16.
//

#ifndef IMOVE_LIGHTTRAILVECTORREPOSITORY_H
#define IMOVE_LIGHTTRAILVECTORREPOSITORY_H


#include "../LightTrail.h"
#include "../../../util/VectorRepository.h"

class LightTrailVectorRepository : public VectorRepository<LightTrail> {
private:
    static LightTrailVectorRepository* _instance;
    LightTrailVectorRepository(){}
public:
    static LightTrailVectorRepository * getInstance();
};


#endif //IMOVE_LIGHTTRAILVECTORREPOSITORY_H
