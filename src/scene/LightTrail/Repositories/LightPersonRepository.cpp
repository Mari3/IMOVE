//
// Created by Wouter Posdijk on 18/05/16.
//

#include "LightPersonRepository.h"

LightPersonRepository *LightPersonRepository::_instance;

LightPersonRepository *LightPersonRepository::getInstance() {
    if(!_instance){
        _instance = new LightPersonRepository();
    }
    return _instance;
}