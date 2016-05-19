//
// Created by Wouter Posdijk on 18/05/16.
//

#include "LightPerson.h"

LightPerson::LightPerson(const Vector2 &location, unsigned int id, PersonType type, util::Range hue) : location(location),
                                                                                                 id(id),
                                                                                                 type(type),
    hue(hue)
{ }

void LightPerson::shiftHue(float shift) {
    hue += shift;
}

void LightPerson::setLocation(Vector2 newLocation) {
    if(previousLocations.size() > 10){
        previousLocations.pop_front();
    }
    previousLocations.push_back(this->location);
    this->location = location;
}

Vector2 LightPerson::getLocation() {
    return location;
}

unsigned int LightPerson::getId() {
    return id;
}





