#include "PeopleIdentifier.h"


PeopleIdentifier::PeopleIdentifier() {}

PeopleIdentifier::PeopleIdentifier(const Boundary& frame_boundary, const Boundary& left_playfield, const Boundary& right_playfield) : frame_boundary(frame_boundary), left_playfield(left_playfield), right_playfield(right_playfield) {}

PeopleIdentifier::~PeopleIdentifier() {}

std::vector<Person> PeopleIdentifier::match(std::vector<Vector2>& locations) {

  // Go over all people detected in the previous frame and determine their new location or delete them
  for (unsigned int i = 0; i < detected_people.size(); i++) {

    // Get closest location to a person
    int index_closest = getClosest(i, locations);
    // If no close location is found, the person is standing still or left the scene

    if (index_closest < 0) {
      // If a person's type is 'None', the person is deleted
      if (detected_people[i].person_type == Person::PersonType::None) {
        detected_people.erase(detected_people.begin() + i);
        --i;
      // If person is standing still ...
      } else if (detected_people[i].movement_type == Person::MovementType::StandingStill) {
        // ... and has not moved in while, change type to 'None'
        if (detected_people[i].getNotMovedCount() <= 0) {
          detected_people[i].person_type = Person::PersonType::None;
        // ... decrease the standing still counter
        } else {
          detected_people[i]. decreaseNotMovedCount();
        }
      // If no location is found and type is not none, person is standing still
      } else {
        detected_people[i].movement_type = Person::MovementType::StandingStill;
        detected_people[i].resetNotMovedCount();
      }
    // If a close location is found ...
  } else {
      if (detected_people[i].person_type == Person::PersonType::None) {
        detected_people.erase(detected_people.begin() + i);
        --i;
      } else {
        //Set location of person to new location
        detected_people[i].setLocation(locations[index_closest]);
        detected_people[i].movement_type = Person::MovementType::Moving;
        // Delete locations that have been taken
        locations.erase(locations.begin() + index_closest);
      }
    }

  }
  // Go over all remaining locations
  for (unsigned int j = 0; j < locations.size(); j++) {
    // Turn unmatched locations into a new person (if location is close to the edge of the frame)
    //if (!frame_boundary.inBounds(locations[j])) {
      Person new_person = Person(locations[j], Person::PersonType::Participant);
      detected_people.push_back(new_person);
    //}
  }

  for (unsigned int k = 0; k < detected_people.size(); k++) {
    if (!left_playfield.inBounds(detected_people[k].getLocation()) && !right_playfield.inBounds(detected_people[k].getLocation())) {
      detected_people[k].person_type = Person::PersonType::None;
    }
  }

  identifyPlayers();

  return detected_people;
}

void PeopleIdentifier::identifyPlayers() {
  int left_player = getClosestToLeftPaddle();
  int right_player = getClosestToRightPaddle();

  if (detected_people.size() > 0) {
    if (left_player != -1)
      detected_people[left_player].person_type = Person::PersonType::Player;
    if (right_player != -1)
      detected_people[right_player].person_type = Person::PersonType::Player;
  }
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
    // Check if location is closer than previous locations and the threshold
    if (distance < min_distance && distance < 50) {
      // Set distance as minimum and index as closest index
      min_distance = distance;
      min_index = i;
    }
  }
  // Return index of closest location
  return min_index;
}

int PeopleIdentifier::getClosestToLeftPaddle() {
  float max_x = 0;
  int max_index = -1;

  for (unsigned int i = 0; i < detected_people.size(); i++) {
    if (detected_people[i].person_type != Person::PersonType::None) {
      detected_people[i].person_type = Person::PersonType::Participant;
      float xco = detected_people[i].getLocation().x;
      if (xco < 100) {
        if (xco > max_x) {
          max_x = xco;
          max_index = i;
        }
      }
    }
  }
  // std::cout << "Closest to left = " + std::to_string(max_x) << std::endl;
  return max_index;
}

int PeopleIdentifier::getClosestToRightPaddle() {
  float min_x = 300;
  int min_index = -1;

  for (unsigned int i = 0; i < detected_people.size(); i++) {
    if (detected_people[i].person_type != Person::PersonType::None) {
      float xco = detected_people[i].getLocation().x;
      if (xco > 180) {
        if (xco < min_x) {
          min_x = xco;
          min_index = i;
        }
      }
    }
  }
  // std::cout << "Closest to right = " + std::to_string(min_x) << std::endl;
  return min_index;
}
