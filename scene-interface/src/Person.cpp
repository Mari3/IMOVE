#include "Person.hpp"

Person::Person(std::list<Vector2> locations, PersonType type, unsigned int id) :
	locations(locations),
	type(type),
	id(id)
{ }

/*--------------------
 * Getters
 * -----------------*/
std::list<Vector2> Person::getLocations() const {
  return this->locations;
}

unsigned int Person::getId() const {
  return this->id;
}

PersonType Person::getPersonType() const {
  return this->type;
}
