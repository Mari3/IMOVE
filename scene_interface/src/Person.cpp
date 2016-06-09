#include <list>

#include "Person.h"

using namespace scene_interface;

scene_interface::Person::Person(
	unsigned int id,
	Vector2 location,
	Person::PersonType person_type,
	Person::MovementType movement_type
) :
	id(id),
	location(location),
	person_type(person_type),
	movement_type(movement_type)
{ }

const unsigned int scene_interface::Person::getId() const {
    return this->id;
}

const Vector2 scene_interface::Person::getLocation() const {
    return this->location;
}

const Person::PersonType scene_interface::Person::getPersonType() const {
	return this->person_type;
}

const Person::MovementType scene_interface::Person::getMovementType() const {
	return this->movement_type;
}
