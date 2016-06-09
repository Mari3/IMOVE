#include <list>

#include "Person.h"

using namespace scene_interface;


Person::Person(unsigned int id, Vector2 location, PersonType person_type, MovementType movement_type) : location(location), id(id), type(person_type), move_type(movement_type) {
	previousLocations = std::list<Vector2>();
	if (id >= count) {
		count = id + 1;
	}
}

Person::Person(Vector2 location, PersonType type) : location(location), type(type) {
    previousLocations = std::list<Vector2>();
    id = count;
    count++;
    move_type = Moving;
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
