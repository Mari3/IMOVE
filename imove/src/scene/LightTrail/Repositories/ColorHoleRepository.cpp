//
// Created by Wouter Posdijk on 18/05/16.
//

#include "ColorHoleRepository.h"

ColorHoleRepository *ColorHoleRepository::_instance;

ColorHoleRepository *ColorHoleRepository::getInstance() {
    if(!_instance){
        _instance = new ColorHoleRepository();
    }
    return _instance;
}