#include "Person.hpp"

using namespace scene_interface_sma;

Person::Person(boost::interprocess::offset_ptr<Vector2Vector> locations, PersonType type, unsigned int id) :
	locations(locations),
	type(type),
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
  return this->type;
}
