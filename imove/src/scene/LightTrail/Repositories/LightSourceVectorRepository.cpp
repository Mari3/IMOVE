//
// Created by Wouter Posdijk on 18/05/16.
//

#include "LightSourceVectorRepository.h"
LightSourceVectorRepository *LightSourceVectorRepository::_instance;

LightSourceVectorRepository *LightSourceVectorRepository::getInstance() {
    if(!_instance){
        _instance = new LightSourceVectorRepository();
    }
    return _instance;
}