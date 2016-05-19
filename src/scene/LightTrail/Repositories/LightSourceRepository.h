//
// Created by Wouter Posdijk on 17/05/16.
//

#ifndef IMOVE_LIGHTSOURCEREPOSITORY_H
#define IMOVE_LIGHTSOURCEREPOSITORY_H


#include "../LightSource.h"
#include "../../../util/VectorRepository.h"

class LightSourceRepository : public VectorRepository<LightSource> {
private:
    static LightSourceRepository* _instance;
    LightSourceRepository(){}
public:
    static LightSourceRepository * getInstance();
};


#endif //IMOVE_LIGHTSOURCEREPOSITORY_H
