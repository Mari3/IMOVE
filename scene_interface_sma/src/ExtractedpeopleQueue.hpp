#ifndef SCENEINTERFACESMA_EXTRACTEDPEOPLEQUEUE_H
#define SCENEINTERFACESMA_EXTRACTEDPEOPLEQUEUE_H

#include <boost/interprocess/offset_ptr.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/deque.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include "Person.hpp"

namespace scene_interface_sma {
	const char* const NAME_EXTRACTEDPEOPLE_QUEUE = "ExtractedpeopleQueue";
	
	//Define an STL compatible allocator of ints that allocates from the managed_shared_memory.
	//This allocator will allow placing containers in the segment
	typedef boost::interprocess::allocator<boost::interprocess::offset_ptr<scene_interface_sma::Person>, boost::interprocess::managed_shared_memory::segment_manager> PersonSMA;
	
	//Alias a vector that uses the previous STL-like allocator so that allocates
	//its values from the segment
	typedef boost::interprocess::vector<boost::interprocess::offset_ptr<scene_interface_sma::Person>, PersonSMA> PersonVector;

	//Define an STL compatible allocator of ints that allocates from the managed_shared_memory.
	//This allocator will allow placing containers in the segment
	typedef boost::interprocess::allocator<boost::interprocess::offset_ptr<PersonVector>, boost::interprocess::managed_shared_memory::segment_manager> ExtractedpeopleQueueSMA;
	
	//Alias a vector that uses the previous STL-like allocator so that allocates
	//its values from the segment
	typedef boost::interprocess::deque<boost::interprocess::offset_ptr<PersonVector>, ExtractedpeopleQueueSMA> ExtractedpeopleQueue;
}

#endif //SCENEINTERFACESMA_EXTRACTEDPEOPLEQUEUE_H
