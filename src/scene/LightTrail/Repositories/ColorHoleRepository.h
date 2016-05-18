//
// Created by Wouter Posdijk on 17/05/16.
//

#ifndef IMOVE_COLORHOLEREPOSITORY_H
#define IMOVE_COLORHOLEREPOSITORY_H


#include "../ColorHole.h"
#include "../../../shared/VectorRepository.h"

class ColorHoleRepository : public VectorRepository<ColorHole> {
private:
    static ColorHoleRepository* _instance;
    ColorHoleRepository(){}
public:
    static ColorHoleRepository *getInstance();
};


#endif //IMOVE_COLORHOLEREPOSITORY_H
