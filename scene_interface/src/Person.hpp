#ifndef SCENEINTERFACE_PERSON_H
#define SCENEINTERFACE_PERSON_H

#include <boost/interprocess/offset_ptr.hpp>
#include <list>
#include "Vector2.hpp"

namespace scene_interface {
	enum PersonType{
	    Bystander,
	    Passerthrough,
	    Participant,
	    None
	};
	
	class Person {
	 public:
	    Person(boost::interprocess::offset_ptr<std::list<boost::interprocess::offset_ptr<scene_interface::Vector2> > > locations, PersonType type, unsigned int id);
	
	    //Getters
	    boost::interprocess::offset_ptr<std::list<boost::interprocess::offset_ptr<scene_interface::Vector2> > > getLocations() const;
	    unsigned int getId() const;
	    PersonType getPersonType() const;
	 
	 private:
	    // List of previous locations
	    const boost::interprocess::offset_ptr<std::list<boost::interprocess::offset_ptr<scene_interface::Vector2> > > locations;
	
			// Person Type
			const PersonType type;
	
	    // Id
	    const unsigned int id;
	};
}

#endif //SCENEINTERFACE_PERSON_H
