#ifndef PERSON_H
#define PERSON_H

#include <list>
#include "../../util/src/Vector2.h"

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
			InterStandingStill,
			InterMoving
		};

    PersonType person_type;
		MovementType movement_type;
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
