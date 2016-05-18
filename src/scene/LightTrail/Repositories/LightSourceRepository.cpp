//
// Created by Wouter Posdijk on 18/05/16.
//

#include "LightSourceRepository.h"
LightSourceRepository *LightSourceRepository::_instance;

LightSourceRepository *LightSourceRepository::getInstance() {
    if(!_instance){
        _instance = new LightSourceRepository();
    }
    return _instance;
}