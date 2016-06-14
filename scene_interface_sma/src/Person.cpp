#include "Person.hpp"

using namespace scene_interface_sma;

Person::Person(boost::interprocess::offset_ptr<Locations> locations, Person::PersonType person_type, Person::MovementType movement_type, unsigned int id) :
	locations(locations),
	person_type(person_type),
	movement_type(movement_type),
	id(id)
{ }

/*--------------------
 * Getters
 * -----------------*/
const boost::interprocess::offset_ptr<Locations> Person::getLocations() const {
  return this->locations;
}

const unsigned int Person::getId() const {
  return this->id;
}

const Person::PersonType Person::getPersonType() const {
  return this->person_type;
}

const Person::MovementType Person::getMovementType() const {
  return this->movement_type;
}
