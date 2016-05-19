//
// Created by Wouter Posdijk on 18/05/16.
//

#include "LightPerson.h"

LightPerson::LightPerson(const Vector2 &location, int id, PersonType type, Range hue) : Person(location,id,type),
    hue(hue)
{ }

void LightPerson::shiftHue(float shift) {
    hue += shift;
}



