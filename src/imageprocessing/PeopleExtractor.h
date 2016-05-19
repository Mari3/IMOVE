//
// Created by Wouter Posdijk on 11/05/16.
//

#ifndef IMOVE_PEOPLEEXTRACTOR_H
#define IMOVE_PEOPLEEXTRACTOR_H


#include <vector>
#include "cameraprojectionmapper/CameraProjectionMapper.h"
#include "detector/PeopleDetector.h"
#include "identifier/PeopleIdentifier.h"
#include "../interface/Person.h"

class PeopleExtractor {
private:
    PeopleDetector detector;
    CameraProjectionMapper mapper;
    PeopleIdentifier identifier;
public:
    virtual vector<Person> read() = 0;
};


#endif //IMOVE_PEOPLEEXTRACTOR_H
