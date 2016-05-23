//
// Created by Wouter Posdijk on 11/05/16.
//

#include "PeopleIdentifier.h"

PeopleIdentifier::PeopleIdentifier() {}
PeopleIdentifier::~PeopleIdentifier() {}

vector<Person> PeopleIdentifier::match(std::vector<Vector2> locations) {
  for (int i = 0; i < detected_people.size(); i++) {
    int index_closest = getClosest(i, locations);
    if (index_closest < 0) {
    // if (detected_people[i].closeToEdge(960,540)) {
        detected_people.erase(detected_people.begin() + i);
        --i;
    // }
    } else {
      Vector2 new_loc = locations[index_closest];
      // if (close to edge) { // check closer to edge than location
      //  delete person
      // }
      detected_people[i].setLocation(new_loc);
      // putText(thresh, std::to_string(detected_people[i].getId()), Point(new_loc.x, new_loc.y), FONT_HERSHEY_SIMPLEX, 1, Scalar(255,0,0));
      locations.erase(locations.begin() + index_closest);
    }
  }
  for (int j = 0; j < locations.size(); j++) {
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
  float min_distance = std::numeric_limits<float>::max();
  int min_index = -1;
  for (int k = 0; k < new_locations.size(); k++) {
    float distance = person.getLocation().distance(new_locations[k]);
    if (distance < min_distance && distance < 50) {
      min_distance = distance;
      min_index = k;
    }
  }
  return min_index;
}
