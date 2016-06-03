#ifndef SCENEINTERFACE_PERSON_H
#define SCENEINTERFACE_PERSON_H

#include <list>
#include "Vector2.h"

namespace scene_interface {
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
	    Person(Vector2 location, PersonType type);
	
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
