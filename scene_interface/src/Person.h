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

	 public:
	    PersonType type;
			MovementType move_type;
			
			Person(unsigned int id, Vector2 location, PersonType person_type, MovementType movement_type);

	    //Getters
	    Vector2 getLocation();
	    unsigned int getId();
	};
}


#endif //SCENEINTERFACE_PERSON_H
