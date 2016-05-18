//
// Created by Wouter Posdijk on 11/05/16.
//

#include "Person.h"

Person::Person(Vector2 location, PersonType type) : location(location), type(type) {
    previousLocations = list<Vector2>();
    id = count;
    count++;
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

int Person::count = 0;

int Person::getId() {
    return id;
}

bool Person::closeToEdge(int width, int height) {
  float edge_width = (width/100)*4;
  float edge_height = (height/100)*4;
  if (this->location.x < edge_width || this->location.x > width - edge_width) {
    return true;
  }
  if (this->location.y < edge_height || this->location.y > height - edge_height) {
    return true;
  }
  return false;
}
