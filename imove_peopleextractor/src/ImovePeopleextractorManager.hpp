#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/offset_ptr.hpp>
#include <vector>

#include "Calibration/Calibration.hpp"
#include "ImageProcessing/PeopleExtractor.h"
//#include <scene_interface_sma/ExtractedpeopleQueue.hpp>
#include "../../scene_interface_sma/src/ExtractedpeopleQueue.hpp"

// Setups people extractor and Scene, can let the Scene run using constant input of people extractor
class ImovePeopleextractorManager {
	public:
		/**
		 * Setup people extractor and communicate to Scene.
		 * 
		 * @param Calibration              The camera projector Calibration
		 **/
		ImovePeopleextractorManager(Calibration* calibration);

		// Run the people extractor and Scene frame by frame
		void run();

	protected:
		Calibration* calibration;
		PeopleExtractor* people_extractor;

		// shared memory segment between extractedpeople and scene
		boost::interprocess::managed_shared_memory* segment;
		// shared memory extracted people queue
		boost::interprocess::offset_ptr<scene_interface_sma::ExtractedpeopleQueue> extractedpeople_queue;
		
		/**
		 * Push extractedpeople on shared memory query for scene to pop.
		 * 
		 * @param extractedpeople Extracted people for scene input
		 **/
		void sendExtractedpeople(scene_interface::People extractedpeople);
};
