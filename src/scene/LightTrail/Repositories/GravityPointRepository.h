//
// Created by Wouter Posdijk on 17/05/16.
//

#ifndef IMOVE_GRAVITYPOINTREPOSITORY_H
#define IMOVE_GRAVITYPOINTREPOSITORY_H


#include "../../../shared/VectorRepository.h"
#include "../GravityPoint.h"

class GravityPointRepository : public VectorRepository<GravityPoint> {
private:
    static GravityPointRepository* _instance;
    GravityPointRepository(){}
public:
    static GravityPointRepository *getInstance();
};


#endif //IMOVE_GRAVITYPOINTREPOSITORY_H
