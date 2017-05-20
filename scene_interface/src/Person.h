#ifndef SCENEINTERFACE_PERSON_H
#define SCENEINTERFACE_PERSON_H

#include "Location.h"

namespace scene_interface {

	class Person {
	 public:
		enum PersonType{
			Bystander,
			Passerthrough,
			Participant,
			Player,
			None
		};

		enum MovementType{
			StandingStill,
			Moving
		};

		Person(unsigned int id, Location location, Person::PersonType person_type, Person::MovementType movement_type);

	    //Getters
	    const unsigned int getId() const;
	    const Location getLocation() const;
			const Person::PersonType getPersonType() const;
			const Person::MovementType getMovementType() const;
	 private:
	    // Id
	    unsigned int id;

	protected:
		// Current location
		Location location;

		// Person type
		PersonType person_type;

		// Movement type
		MovementType movement_type;
	};
}


#endif //SCENEINTERFACE_PERSON_H
