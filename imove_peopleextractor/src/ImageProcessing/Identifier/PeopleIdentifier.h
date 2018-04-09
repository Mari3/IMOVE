//
// Created by Wouter Posdijk on 11/05/16.
//

#ifndef IMOVE_SRC_IMAGE_PROCESSING_IDENTIFIER_PEOPLEIDENTIFIER_H_
#define IMOVE_SRC_IMAGE_PROCESSING_IDENTIFIER_PEOPLEIDENTIFIER_H_

#include <limits>
#include <vector>

#include "../../../../util/src/Boundary.h"
#include "../../Person.h"

class PeopleIdentifier {
 private:
  // Vector containing detected people in the frame
  std::vector<Person> detected_people;

  // Boundary of projection to seperate bystanders from participants
  Boundary projection_boundary;

  // Get closest location to a Person
  int getClosest(unsigned int index, std::vector<Vector2>& new_locations);

 public:
  PeopleIdentifier();
  PeopleIdentifier(const Boundary& projection_boundary);
  ~PeopleIdentifier();

  // Match people to new locations and locations to (new) people
  std::vector<Person> match(std::vector<Vector2>& locations);
};


#endif  // IMOVE_SRC_IMAGE_PROCESSING_IDENTIFIER_PEOPLEIDENTIFIER_H_
