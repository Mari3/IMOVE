#include <boost/interprocess/offset_ptr.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/deque.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include "People.hpp"

namespace scene_interface_sma {
	const char* const NAME_PEOPLE_QUEUE = "PeopleQueue";
	
	//Define an STL compatible allocator of ints that allocates from the managed_shared_memory.
	//This allocator will allow placing containers in the segment
	typedef boost::interprocess::allocator<boost::interprocess::offset_ptr<People>, boost::interprocess::managed_shared_memory::segment_manager> PeopleQueueSMA;
	
	//Alias a vector that uses the previous STL-like allocator so that allocates
	//its values from the segment
	typedef boost::interprocess::deque<boost::interprocess::offset_ptr<People>, PeopleQueueSMA> PeopleQueue;
}
