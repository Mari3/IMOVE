#include <boost/interprocess/offset_ptr.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include "Locations.hpp"

namespace scene_interface_sma {
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

	    Person(boost::interprocess::offset_ptr<Locations> locations, PersonType person_type, MovementType movement_type, unsigned int id);

	    //Getters
	    const boost::interprocess::offset_ptr<Locations> getLocations() const;
	    const unsigned int getId() const;
	    const PersonType getPersonType() const;
	    const MovementType getMovementType() const;

	 private:
	    // List of previous locations
	    const boost::interprocess::offset_ptr<Locations> locations;

			// Person Type
			const PersonType person_type;

			// Movement Type
			const MovementType movement_type;

	    // Id
	    const unsigned int id;
	};
}
