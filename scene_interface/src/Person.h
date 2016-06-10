#ifndef SCENEINTERFACE_PERSON_H
#define SCENEINTERFACE_PERSON_H

#include <list>
#include "Vector2.h"

namespace scene_interface {

	class Person {
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
			
			Person(unsigned int id, Vector2 location, Person::PersonType person_type, Person::MovementType movement_type);

	    //Getters
	    const unsigned int getId() const;
	    const Vector2 getLocation() const;
			const Person::PersonType getPersonType() const;
			const Person::MovementType getMovementType() const;
	 private:
	    // Id
	    unsigned int id;

	    // Current location
	    Vector2 location;
	   
			// Person type
			PersonType person_type;

			// Movement type
			MovementType movement_type;
	};
}


#endif //SCENEINTERFACE_PERSON_H
