#include "LightPerson.h"

LightPerson::LightPerson(const scene_interface::Vector2 &location, unsigned int id, scene_interface::PersonType type, util::Range hue) : location(location),
                                                                                                 id(id),
                                                                                                 type(type),
    hue(hue)
{ }

void LightPerson::shiftHue(float shift) {
    hue += shift;
}

void LightPerson::setLocation(scene_interface::Vector2 newLocation) {
    //Store the 10 previous locations
    if (previousLocations.size() > 10) {
        previousLocations.pop_front();
    }
    previousLocations.push_back(location);
    location = newLocation;
}

scene_interface::Vector2 LightPerson::getLocation() {
    return location;
}

unsigned int LightPerson::getId() {
    return id;
}
