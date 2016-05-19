//
// Created by Wouter Posdijk on 18/05/16.
//

#ifndef IMOVE_PERSONTURNEDBYSTANDERCONDITION_H
#define IMOVE_PERSONTURNEDBYSTANDERCONDITION_H


#include "../Repositories/LightPersonRepository.h"
#include "../../Condition.h"

class PersonChangedTypeCondition : public Condition {
private:
    LightPersonRepository* lightPeople;
    std::map<int,PersonType> oldType;
public:
    PersonChangedTypeCondition();
    int check(float dt, Action **&actions) override;

public:

};


#endif //IMOVE_PERSONTURNEDBYSTANDERCONDITION_H
