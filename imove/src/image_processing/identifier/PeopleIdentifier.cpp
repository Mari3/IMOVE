//
// Created by Wouter Posdijk on 11/05/16.
//

#include "PeopleIdentifier.h"

PeopleIdentifier::PeopleIdentifier() {}
PeopleIdentifier::~PeopleIdentifier() {}

vector<Person> PeopleIdentifier::match(std::vector<Vector2> locations) {
  // Go over all people detected in the previous frame and determine their new location or delete them
  for (unsigned int i = 0; i < detected_people.size(); i++) {
    // Get closest location to a person
    int index_closest = getClosest(i, locations);
    // If no close location is found, delete person
    if (index_closest < 0) {
    // if (detected_people[i].closeToEdge(960,540)) {
        detected_people.erase(detected_people.begin() + i);
        --i;
    // }
    } else {
      //Set location of person to new location
      Vector2 new_location = locations[index_closest];
      // if (close to edge) { // check closer to edge than location
      //  delete person
      // }
      detected_people[i].setLocation(new_location);
      // putText(thresh, std::to_string(detected_people[i].getId()), Point(new_loc.x, new_loc.y), FONT_HERSHEY_SIMPLEX, 1, Scalar(255,0,0));
      // Delete locations that have been taken
      locations.erase(locations.begin() + index_closest);
    }
  }
  // Go over all remaining locations and turn them into a new person
  for (unsigned int j = 0; j < locations.size(); j++) {
    Person new_person = Person(locations[j], Participant);
    // if (!new_person.closeToEdge(480, 270)) {
      // new_locations.erase(locations.begin() + j);
      // --j;
    // }
    // else {
      detected_people.push_back(new_person);
      // putText(thresh, std::to_string(new_person.getId()), Point(new_locations[j].x, new_locations[j].y), FONT_HERSHEY_SIMPLEX, 1, Scalar(255,0,0));
    // }
  }
  // imshow("Frame", thresh);
  return detected_people;
}

int PeopleIdentifier::getClosest(int index, vector<Vector2> new_locations) {
  Person person = detected_people[index];
  // Initialize minimum distance
  float min_distance = std::numeric_limits<float>::max();
  // Initialize min index
  int min_index = -1;

  for (unsigned int i = 0; i < new_locations.size(); i++) {
    // Calculate distance between current person and location
    float distance = person.getLocation().distance(new_locations[i]);
    // Set distance as minimum and index as closest index if location is closer than previous locations and the threshold
    if (distance < min_distance && distance < 50) {
      min_distance = distance;
      min_index = i;
    }
  }
  // Return index of closest location
  return min_index;
}
