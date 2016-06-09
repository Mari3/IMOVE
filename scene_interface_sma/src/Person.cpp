#include "Person.hpp"

using namespace scene_interface_sma;

Person::Person(boost::interprocess::offset_ptr<Vector2Vector> locations, PersonType person_type, MovementType movement_type, unsigned int id) :
	locations(locations),
	person_type(person_type),
	movement_type(movement_type),
	id(id)
{ }

/*--------------------
 * Getters
 * -----------------*/
const boost::interprocess::offset_ptr<Vector2Vector> Person::getLocations() const {
  return this->locations;
}

const unsigned int Person::getId() const {
  return this->id;
}

const PersonType Person::getPersonType() const {
  return this->person_type;
}

const MovementType Person::getMovementType() const {
  return this->movement_type;
}
