#include "PeopleIdentifier.h"
#include "../../../../scene_interface/src/Person.h"

PeopleIdentifier::PeopleIdentifier() {}

PeopleIdentifier::PeopleIdentifier(Boundary boundary) : boundary(boundary) {}

PeopleIdentifier::PeopleIdentifier(std::vector<scene_interface::Person>& people, Boundary boundary) : detected_people(people), boundary(boundary) {}

PeopleIdentifier::~PeopleIdentifier() {}

std::vector<scene_interface::Person> PeopleIdentifier::match(std::vector<scene_interface::Vector2>& locations) {
  // Go over all people detected in the previous frame and determine their new location or delete them
  for (unsigned int i = 0; i < detected_people.size(); i++) {
    // Get closest location to a person
    int index_closest = getClosest(i, locations);
    // If no close location is found, delete person
    if (index_closest < 0) {
      if (detected_people[i].type == scene_interface::None) {
        detected_people.erase(detected_people.begin() + i);
        --i;
      } else if (detected_people[i].type == scene_interface::StandingStill) {
        if (!boundary.inBounds(detected_people[i].getLocation())) {
          detected_people.erase(detected_people.begin() + i);
          --i;
        } else if (detected_people[i].getNotMovedCount() <= 0) {
          detected_people[i].type = scene_interface::None;
        } else {
          detected_people[i]. decreaseNotMovedCount();
        }
      } else {
        detected_people[i].type = scene_interface::StandingStill;
        detected_people[i].resetNotMovedCount();
      }
    } else {
      //Set location of person to new location
      scene_interface::Vector2 new_location = locations[index_closest];
      detected_people[i].setLocation(new_location);
      // Delete locations that have been taken
      locations.erase(locations.begin() + index_closest);
    }
  }
  // Go over all remaining locations and turn them into a new person
  for (unsigned int j = 0; j < locations.size(); j++) {
    scene_interface::Person new_person = scene_interface::Person(locations[j], scene_interface::Participant);
    detected_people.push_back(new_person);
  }
  return detected_people;
}

int PeopleIdentifier::getClosest(unsigned int index, std::vector<scene_interface::Vector2>& new_locations) {
  scene_interface::Person person = detected_people[index];
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
