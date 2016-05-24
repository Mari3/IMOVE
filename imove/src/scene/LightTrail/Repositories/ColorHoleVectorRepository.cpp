//
// Created by Wouter Posdijk on 18/05/16.
//

#include "ColorHoleVectorRepository.h"

ColorHoleVectorRepository *ColorHoleVectorRepository::_instance;

ColorHoleVectorRepository *ColorHoleVectorRepository::getInstance() {
    if(!_instance){
        _instance = new ColorHoleVectorRepository();
    }
    return _instance;
}