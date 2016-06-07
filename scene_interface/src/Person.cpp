#include <list>

#include "Person.h"

using namespace scene_interface;

Person::Person(Vector2 location, PersonType type) : location(location), type(type) {
    previousLocations = std::list<Vector2>();
    id = count;
    count++;
}

Person::Person(unsigned int id, Vector2 location, PersonType type) : location(location), id(id), type(type) {
    previousLocations = std::list<Vector2>();
    if (id >= count) {
			count = id + 1;
		}
}

/*--------------------
 * Getters and setters
 * -----------------*/
Vector2 Person::getLocation() {
    return location;
}

void Person::setLocation(Vector2 location) {
    if(previousLocations.size() > 10){
        previousLocations.pop_front();
    }
    previousLocations.push_back(this->location);
    this->location = location;
}

unsigned int Person::count = 0;

unsigned int Person::getId() {
    return id;
}

unsigned int Person::getNotMovedCount() {
  return not_moved_count;
}

void Person::decreaseNotMovedCount() {
  not_moved_count--;
}

void Person::resetNotMovedCount() {
  not_moved_count = 100;
}
