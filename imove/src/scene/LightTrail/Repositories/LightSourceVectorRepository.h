//
// Created by Wouter Posdijk on 17/05/16.
//

#ifndef IMOVE_LIGHTSOURCEVECTORREPOSITORY_H
#define IMOVE_LIGHTSOURCEVECTORREPOSITORY_H


#include "../LightSource.h"
#include "../../../util/VectorRepository.h"

class LightSourceVectorRepository : public VectorRepository<LightSource> {
private:
    static LightSourceVectorRepository* _instance;
    LightSourceVectorRepository(){}
public:
    static LightSourceVectorRepository * getInstance();
};


#endif //IMOVE_LIGHTSOURCEVECTORREPOSITORY_H
