#include <list>

#include "Person.h"


Person::Person(const Vector2& location, const PersonType person_type) : location(location), person_type(person_type) {
    previousLocations = std::list<Vector2>();
    id = count;
    count++;
    movement_type = Person::MovementType::Moving;
}

/*--------------------
 * Getters and setters
 * -----------------*/
Vector2 Person::getLocation() {
    return location;
}

void Person::setLocation(const Vector2& location) {
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
  not_moved_count = 1000;
}
