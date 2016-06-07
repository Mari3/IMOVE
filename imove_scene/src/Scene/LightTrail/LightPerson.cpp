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
    //Store the 10 previous locations
    if (previousLocations.size() > 10) {
        previousLocations.pop_front();
    }
    previousLocations.push_back(location);
    location = newLocation;
}

Vector2 LightPerson::getLocation() {
    return location;
}

unsigned int LightPerson::getId() {
    return id;
}
