//
// Created by Wouter Posdijk on 11/05/16.
//

#ifndef IMOVE_PEOPLEIDENTIFIER_H
#define IMOVE_PEOPLEIDENTIFIER_H

#include "../../interface/Person.h"
#include "../../util/Vector2.h"
#include <vector>
#include <limits>

using namespace std;


class PeopleIdentifier {

private:


  vector<Person> detected_people;

public:

  PeopleIdentifier();
  ~PeopleIdentifier();

  //Match people to new locations
  vector<Person> match(std::vector<Vector2> locations);

  //Get closest location to a Person
  int getClosest(int index, vector<Vector2> new_locations);

};


#endif //IMOVE_PEOPLEIDENTIFIER_H
