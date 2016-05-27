//
// Created by Wouter Posdijk on 11/05/16.
//

#ifndef IMOVE_PERSON_H
#define IMOVE_PERSON_H

#include <list>
#include "../Util/Vector2.h"

using namespace std;

enum PersonType{
    Bystander,
    Passerthrough,
    Participant,
    None
};

class Person {
 private:
    // List of previous locations
    list<Vector2> previousLocations;

    // Current location
    Vector2 location;

    // Id
    unsigned int id;

    // Object counter to create unique ids
    static unsigned int count;

 public:
    PersonType type;
    Person(Vector2 location, PersonType type);

    //Getters and setters
    Vector2 getLocation();
    void setLocation(Vector2 location);
    unsigned int getId();
};


#endif //IMOVE_PERSON_H
