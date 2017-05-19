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

    // Counter to check how long a person has not moved
    unsigned int not_moved_count = 1000;

 public:
		enum PersonType{
		    Bystander,
		    Participant,
        Player,
		    None
		};

		enum MovementType{
			StandingStill,
			Moving
		};

    // Type of person according to position on the scene
    PersonType person_type;
    // Moving or standing still
		MovementType movement_type;

		Person(const Vector2& location, const PersonType type);

    //Getters and setters
    Vector2 getLocation();
		void setLocation(const Vector2& location);
    unsigned int getId();
	  unsigned int getNotMovedCount();

	  void decreaseNotMovedCount();
	  void resetNotMovedCount();
};

#endif //PERSON_H
