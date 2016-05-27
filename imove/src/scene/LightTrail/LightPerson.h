//
// Created by Wouter Posdijk on 18/05/16.
//

#ifndef IMOVE_LIGHTPERSON_H
#define IMOVE_LIGHTPERSON_H


#include "../../util/Vector2.h"
#include "../../interface/Person.h"
#include "../Util/Range.h"

class LightPerson{
private:
    Vector2 location;
    list<Vector2> previousLocations;
    unsigned int id;
public:
    PersonType type;
    LightPerson(const Vector2 &location, unsigned int id, PersonType type, util::Range hue);
    void shiftHue(float shift);
    void setLocation(Vector2 newLocation);
    Vector2 getLocation();
    unsigned int getId();
    util::Range hue;
};


#endif //IMOVE_LIGHTPERSON_H
