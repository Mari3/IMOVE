//
// Created by Wouter Posdijk on 11/05/16.
//

#ifndef IMOVE_SRC_IMAGE_PROCESSING_IDENTIFIER_PEOPLEIDENTIFIER_H_
#define IMOVE_SRC_IMAGE_PROCESSING_IDENTIFIER_PEOPLEIDENTIFIER_H_

#include <limits>
#include <vector>

#include "../../Interface/Person.h"
#include "../../Util/Vector2.h"

class PeopleIdentifier {
 private:
  // Vector containing detected people in the frame
  vector<Person> detected_people;

 public:
  PeopleIdentifier();
  ~PeopleIdentifier();

  // Match people to new locations
  vector<Person> match(std::vector<Vector2>& locations);

  // Get closest location to a Person
  int getClosest(unsigned int index, vector<Vector2>& new_locations);
};


#endif  // IMOVE_SRC_IMAGE_PROCESSING_IDENTIFIER_PEOPLEIDENTIFIER_H_
