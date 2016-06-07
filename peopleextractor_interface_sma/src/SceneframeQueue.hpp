#ifndef PEOPLEEXTRACTORINTERFACESMA_SCENEFRAMEQUEUE_H
#define PEOPLEEXTRACTORINTERFACESMA_SCENEFRAMEQUEUE_H

#include <boost/interprocess/offset_ptr.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/deque.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <string>

#include "Image.hpp"

namespace peopleextractor_interface_sma {
	//Define an STL compatible allocator of ints that allocates from the managed_shared_memory.
	//This allocator will allow placing containers in the segment
	typedef boost::interprocess::allocator<boost::interprocess::offset_ptr<Image>, boost::interprocess::managed_shared_memory::segment_manager> SceneframeQueueSMA;
	
	//Alias a deque that uses the previous STL-like allocator so that allocates its values from the segment
	typedef boost::interprocess::deque<boost::interprocess::offset_ptr<Image>, SceneframeQueueSMA> SceneframeQueue;

	const char* const NAME_SCENEFRAME_QUEUE = "SceneframeQueue";
}

#endif //PEOPLEEXTRACTORINTERFACESMA_SCENEFRAMEQUEUE_H
