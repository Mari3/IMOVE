#ifndef SCENEINTERFACE_PERSON_H
#define SCENEINTERFACE_PERSON_H

#include <list>
#include "Vector2.h"

namespace scene_interface {
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
	    Person(Vector2 location, PersonType type);
			Person(unsigned int id, Vector2 location, PersonType person_type, MovementType movement_type);

	    //Getters and setters
	    Vector2 getLocation();
	    void setLocation(Vector2 location);
	    unsigned int getId();
	    unsigned int getNotMovedCount();

	    void decreaseNotMovedCount();
	    void resetNotMovedCount();
	};
}


#endif //SCENEINTERFACE_PERSON_H
