#include "PeopleIdentifier.h"

PeopleIdentifier::PeopleIdentifier() {}

PeopleIdentifier::PeopleIdentifier(Boundary projection_boundary, Boundary frame_boundary) : projection_boundary(projection_boundary), frame_boundary(frame_boundary) {}

PeopleIdentifier::PeopleIdentifier(std::vector<Person>& people, Boundary projection_boundary, Boundary frame_boundary) : detected_people(people), projection_boundary(projection_boundary), frame_boundary(frame_boundary) {}

PeopleIdentifier::~PeopleIdentifier() {}

std::vector<Person> PeopleIdentifier::match(std::vector<Vector2>& locations) {
  // Go over all people detected in the previous frame and determine their new location or delete them
  for (unsigned int i = 0; i < detected_people.size(); i++) {
    // Get closest location to a person
    int index_closest = getClosest(i, locations);
    // If no close location is found, delete person
    if (index_closest < 0) {
      if (detected_people[i].person_type == Person::PersonType::None) {
        detected_people.erase(detected_people.begin() + i);
        --i;
      } else if (detected_people[i].movement_type == Person::MovementType::StandingStill) {
        if (!frame_boundary.inBounds(detected_people[i].getLocation())) {
          detected_people.erase(detected_people.begin() + i);
          --i;
        } else if (detected_people[i].getNotMovedCount() <= 0) {
          detected_people[i].person_type = Person::PersonType::None;
        } else {
          detected_people[i]. decreaseNotMovedCount();
        }
      } else {
        detected_people[i].movement_type = Person::MovementType::StandingStill;
        detected_people[i].resetNotMovedCount();
      }
    } else {
      if (projection_boundary.inBounds(locations[index_closest])) {
        detected_people[i].person_type = Person::PersonType::Participant;
      }
      else {
        detected_people[i].person_type = Person::PersonType::Bystander;
      }
      //Set location of person to new location
      detected_people[i].setLocation(locations[index_closest]);
      detected_people[i].movement_type = Person::MovementType::Moving;
      // Delete locations that have been taken
      locations.erase(locations.begin() + index_closest);
    }
  }
  // Go over all remaining locations and turn them into a new person
  for (unsigned int j = 0; j < locations.size(); j++) {
    if (!projection_boundary.inBounds(locations[j])) {
      Person new_person = Person(locations[j], Person::PersonType::Bystander);
      detected_people.push_back(new_person);
    }
  }
  return detected_people;
}

int PeopleIdentifier::getClosest(unsigned int index, std::vector<Vector2>& new_locations) {
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
