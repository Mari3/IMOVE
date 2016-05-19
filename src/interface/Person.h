//
// Created by Wouter Posdijk on 11/05/16.
//

#ifndef IMOVE_PERSON_H
#define IMOVE_PERSON_H

#include <list>
#include "../util/Vector2.h"

using namespace std;

enum PersonType{
    Bystander,
    Passerthrough,
    Participant
};

class Person {
private:
    list<Vector2> previousLocations;
    Vector2 location;
    unsigned int id;
public:
    PersonType type;
    Person(Vector2 location, unsigned int id, PersonType type);
    //Getters and setters
    Vector2 getLocation();
    void setLocation(Vector2 location);
    unsigned int getId();
};


#endif //IMOVE_PERSON_H
