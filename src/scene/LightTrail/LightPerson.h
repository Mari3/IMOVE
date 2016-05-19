//
// Created by Wouter Posdijk on 18/05/16.
//

#ifndef IMOVE_LIGHTPERSON_H
#define IMOVE_LIGHTPERSON_H


#include "../../util/Vector2.h"
#include "../../interface/Person.h"
#include "../../util/Range.h"

class LightPerson : public Person{
public:
    LightPerson(const Vector2 &location, int id, PersonType type, Range hue);
    void shiftHue(float shift);
    Range hue;
};


#endif //IMOVE_LIGHTPERSON_H
