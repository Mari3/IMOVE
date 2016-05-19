//
// Created by Wouter Posdijk on 18/05/16.
//

#include "GravityPointRepository.h"

GravityPointRepository *GravityPointRepository::_instance;

GravityPointRepository *GravityPointRepository::getInstance() {
    if(!_instance){
        _instance = new GravityPointRepository();
    }
    return _instance;
}