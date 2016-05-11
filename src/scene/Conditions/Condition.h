//
// Created by Wouter Posdijk on 11/05/16.
//

#ifndef IMOVE_CONDITION_H
#define IMOVE_CONDITION_H

#include "../Actions/Action.h"

class Condition{
public:
    virtual int check(float dt, Action**& actions) = 0;
};

#endif //IMOVE_CONDITION_H
