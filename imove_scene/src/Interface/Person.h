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
    StandingStill,
    None
};

class Person {
 private:
    // List of previous locations
    list<Vector2> previousLocations;

    // Id
    unsigned int id;

    // Current location
    Vector2 location;

    // Object counter to create unique ids
    static unsigned int count;

    //
    unsigned int not_moved_count = 100;

 public:
    Person(Vector2 location, PersonType type);
    Person(unsigned int id, Vector2 location, PersonType type);
    
		PersonType type;

    //Getters and setters
    Vector2 getLocation();
    void setLocation(Vector2 location);
    unsigned int getId();
    unsigned int getNotMovedCount();

    void decreaseNotMovedCount();
    void resetNotMovedCount();
};


#endif //IMOVE_PERSON_H
