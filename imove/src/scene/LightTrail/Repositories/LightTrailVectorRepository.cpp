//
// Created by Wouter Posdijk on 18/05/16.
//

#include "LightTrailVectorRepository.h"

LightTrailVectorRepository *LightTrailVectorRepository::_instance;

LightTrailVectorRepository *LightTrailVectorRepository::getInstance() {
    if(!_instance){
        _instance = new LightTrailVectorRepository();
    }
    return _instance;
}