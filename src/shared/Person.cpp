//
// Created by Wouter Posdijk on 11/05/16.
//

#include "Person.h"

Person::Person(Vector2 location, unsigned int id, PersonType type) : location(location), id(id), type(type) {
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

unsigned int Person::getId() {
    return id;
}









