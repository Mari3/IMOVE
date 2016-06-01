//
// Created by Wouter Posdijk on 11/05/16.
//

#include <assert.h>
#include "Person.h"

Person::Person(Vector2 location, PersonType type) : location(location), type(type) {
    previousLocations = list<Vector2>();
    id = count;
    count++;
}
Person::Person(unsigned int id, Vector2 location, PersonType type) : id(id), location(location), type(type) {
		assert(id < count || count == 0);
    previousLocations = list<Vector2>();
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
