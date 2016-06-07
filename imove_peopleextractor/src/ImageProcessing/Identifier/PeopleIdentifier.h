//
// Created by Wouter Posdijk on 11/05/16.
//

#ifndef IMOVE_SRC_IMAGE_PROCESSING_IDENTIFIER_PEOPLEIDENTIFIER_H_
#define IMOVE_SRC_IMAGE_PROCESSING_IDENTIFIER_PEOPLEIDENTIFIER_H_

#include <limits>
#include <vector>
#include <iostream>

#include "../../../../scene_interface/src/Person.h"
#include "../../../../scene_interface/src/Boundary.h"

class PeopleIdentifier {
 private:
  // Vector containing detected people in the frame
  std::vector<scene_interface::Person> detected_people;

  //
  Boundary boundary;

 public:
  PeopleIdentifier();
  PeopleIdentifier(Boundary boundary);
  PeopleIdentifier(std::vector<scene_interface::Person>& people, Boundary boundary);
  ~PeopleIdentifier();

  // Match people to new locations
  std::vector<scene_interface::Person> match(std::vector<scene_interface::Vector2>& locations);

  // Get closest location to a Person
  int getClosest(unsigned int index, std::vector<scene_interface::Vector2>& new_locations);
};


#endif  // IMOVE_SRC_IMAGE_PROCESSING_IDENTIFIER_PEOPLEIDENTIFIER_H_
