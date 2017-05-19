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

  // Boundary of frame
  Boundary frame_boundary;

  //Boundaries of left and right playfield zone
  Boundary left_playfield;
  Boundary right_playfield;

  // Get closest location to a Person
  int getClosest(unsigned int index, std::vector<Vector2>& new_locations);

  void identifyPlayers();

  int getClosestToLeftPaddle();
  int getClosestToRightPaddle();

 public:
  PeopleIdentifier();
  PeopleIdentifier(const Boundary& frame_boundary, const Boundary& left_playfield, const Boundary& right_playfield);
  ~PeopleIdentifier();

  // Match people to new locations and locations to (new) people
  std::vector<Person> match(std::vector<Vector2>& locations);
};


#endif  // IMOVE_SRC_IMAGE_PROCESSING_IDENTIFIER_PEOPLEIDENTIFIER_H_
