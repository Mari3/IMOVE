//
// Created by Wouter Posdijk on 18/05/16.
//

#include "LightPersonMapRepository.h"

LightPersonMapRepository *LightPersonMapRepository::_instance;

LightPersonMapRepository *LightPersonMapRepository::getInstance() {
    if(!_instance){
        _instance = new LightPersonMapRepository();
    }
    return _instance;
}