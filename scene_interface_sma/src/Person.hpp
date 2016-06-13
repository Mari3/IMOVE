#include <boost/interprocess/offset_ptr.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include "Locations.hpp"

namespace scene_interface_sma {
	enum PersonType{
	    Bystander,
	    Passerthrough,
	    Participant,
			StandingStill,
	    None
	};
	
	
	class Person {
	 public:
	    Person(boost::interprocess::offset_ptr<Locations> locations, PersonType type, unsigned int id);
	
	    //Getters
	    const boost::interprocess::offset_ptr<Locations> getLocations() const;
	    const unsigned int getId() const;
	    const scene_interface_sma::PersonType getPersonType() const;
	 
	 private:
	    // List of previous locations
	    const boost::interprocess::offset_ptr<Locations> locations;
	
			// scene_interface_sma::Person Type
			const PersonType type;
	
	    // Id
	    const unsigned int id;
	};
}
