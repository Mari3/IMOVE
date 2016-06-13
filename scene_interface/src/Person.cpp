#include "Person.h"

using namespace scene_interface;

Person::Person(
	unsigned int id,
	Location location,
	Person::PersonType person_type,
	Person::MovementType movement_type
) :
	id(id),
	location(location),
	person_type(person_type),
	movement_type(movement_type)
{ }

const unsigned int Person::getId() const {
    return this->id;
}

const Location Person::getLocation() const {
    return this->location;
}

const Person::PersonType Person::getPersonType() const {
	return this->person_type;
}

const Person::MovementType Person::getMovementType() const {
	return this->movement_type;
}
