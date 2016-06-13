//
// Created by Wouter Posdijk on 11/05/16.
//

#ifndef IMOVE_SRC_IMAGE_PROCESSING_IDENTIFIER_PEOPLEIDENTIFIER_H_
#define IMOVE_SRC_IMAGE_PROCESSING_IDENTIFIER_PEOPLEIDENTIFIER_H_

#include <limits>
#include <vector>
#include <iostream>

#include "../../../../scene_interface/src/Boundary.h"
#include "../../Person.h"

class PeopleIdentifier {
 private:
  // Vector containing detected people in the frame
  std::vector<Person> detected_people;

  //
  Boundary projection_boundary;
  Boundary frame_boundary;

 public:
  PeopleIdentifier();
  PeopleIdentifier(Boundary projection_boundary, Boundary frame_boundary);
  PeopleIdentifier(std::vector<Person>& people, Boundary projection_boundary, Boundary frame_boundary);
  ~PeopleIdentifier();

  // Match people to new locations
  std::vector<Person> match(std::vector<Vector2>& locations);

  // Get closest location to a Person
  int getClosest(unsigned int index, std::vector<Vector2>& new_locations);

};


#endif  // IMOVE_SRC_IMAGE_PROCESSING_IDENTIFIER_PEOPLEIDENTIFIER_H_
