#ifndef SCENEINTERFACE_PERSON_H
#define SCENEINTERFACE_PERSON_H

#include <list>
#include "Vector2.hpp"

using namespace std;

enum PersonType{
    Bystander,
    Passerthrough,
    Participant,
    None
};

class Person {
 public:
    Person(std::list<Vector2> locations, PersonType type, unsigned int id);

    //Getters
    std::list<Vector2> getLocations() const;
    unsigned int getId() const;
    PersonType getPersonType() const;
 
 private:
    // List of previous locations
    const std::list<Vector2> locations;

		// Person Type
		const PersonType type;

    // Id
    const unsigned int id;
};

#endif //SCENEINTERFACE_PERSON_H
