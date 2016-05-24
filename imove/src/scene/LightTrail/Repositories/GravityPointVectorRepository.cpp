//
// Created by Wouter Posdijk on 18/05/16.
//

#include "GravityPointVectorRepository.h"

GravityPointVectorRepository *GravityPointVectorRepository::_instance;

GravityPointVectorRepository *GravityPointVectorRepository::getInstance() {
    if(!_instance){
        _instance = new GravityPointVectorRepository();
    }
    return _instance;
}