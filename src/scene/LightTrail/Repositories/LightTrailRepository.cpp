//
// Created by Wouter Posdijk on 18/05/16.
//

#include "LightTrailRepository.h"

LightTrailRepository *LightTrailRepository::_instance;

LightTrailRepository *LightTrailRepository::getInstance() {
    if(!_instance){
        _instance = new LightTrailRepository();
    }
    return _instance;
}