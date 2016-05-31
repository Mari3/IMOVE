#include "Person.hpp"

using namespace scene_interface;

scene_interface::Person::Person(boost::interprocess::offset_ptr<std::list<boost::interprocess::offset_ptr<scene_interface::Vector2> > > locations, scene_interface::PersonType type, unsigned int id) :
	locations(locations),
	type(type),
	id(id)
{ }

/*--------------------
 * Getters
 * -----------------*/
boost::interprocess::offset_ptr<std::list<boost::interprocess::offset_ptr<scene_interface::Vector2> > > scene_interface::Person::getLocations() const {
  return this->locations;
}

unsigned int scene_interface::Person::getId() const {
  return this->id;
}

scene_interface::PersonType scene_interface::Person::getPersonType() const {
  return this->type;
}
