//
// Created by Wouter Posdijk on 17/05/16.
//

#ifndef IMOVE_COLORHOLEVECTORREPOSITORY_H
#define IMOVE_COLORHOLEVECTORREPOSITORY_H


#include "../ColorHole.h"
#include "../../../util/VectorRepository.h"

class ColorHoleVectorRepository : public VectorRepository<ColorHole> {
private:
    static ColorHoleVectorRepository* _instance;
    ColorHoleVectorRepository(){}
public:
    static ColorHoleVectorRepository *getInstance();
};


#endif //IMOVE_COLORHOLEREPOSITORY_H
