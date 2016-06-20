#include "LightPerson.h"

LightPerson::LightPerson(const Vector2 &location, unsigned int id, scene_interface::Person::PersonType person_type,
                         scene_interface::Person::MovementType movement_type, util::Range hue,
                         Repository<LightTrail> *trails) :
        location(location),
        id(id),
        person_type(person_type),
        movement_type(movement_type),
        hue(hue), trails(trails) { }

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


