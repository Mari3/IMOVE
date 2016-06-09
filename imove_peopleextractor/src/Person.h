#ifndef PERSON_H
#define PERSON_H

#include <list>
#include "Vector2.h"

enum PersonType{
    Bystander,
    Passerthrough,
    Participant,
    None
};

enum MovementType{
	StandingStill,
	Moving
};

enum InterframeType{
	StandingStill,
	Moving
};

class Person {
 private:
    // List of previous locations
    std::list<Vector2> previousLocations;

    // Current location
    Vector2 location;

    // Id
    unsigned int id;

    // Object counter to create unique ids
    static unsigned int count;

    //
    unsigned int not_moved_count = 100;

 public:
    PersonType type;
		MovementType move_type;
		InterframeType interframe_type;
 
		Person(Vector2 location, PersonType type);

    //Getters and setters
    Vector2 getLocation();
		void setLocation(Vector2 location);
    unsigned int getId();
	  unsigned int getNotMovedCount();

	  void decreaseNotMovedCount();
	  void resetNotMovedCount();
};

#endif //PERSON_H
