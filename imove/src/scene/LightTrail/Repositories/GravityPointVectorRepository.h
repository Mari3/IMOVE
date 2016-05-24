//
// Created by Wouter Posdijk on 17/05/16.
//

#ifndef IMOVE_GRAVITYPOINTVECTORREPOSITORY_H
#define IMOVE_GRAVITYPOINTVECTORREPOSITORY_H


#include "../../../util/VectorRepository.h"
#include "../GravityPoint.h"

class GravityPointVectorRepository : public VectorRepository<GravityPoint> {
private:
    static GravityPointVectorRepository* _instance;
    GravityPointVectorRepository(){}
public:
    static GravityPointVectorRepository *getInstance();
};


#endif //IMOVE_GRAVITYPOINTREPOSITORY_H
