#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/offset_ptr.hpp>
#include <vector>

#include "../../util/src/configuration/ImoveConfiguration.hpp"
#include "../../util/src/Projection.hpp"
#include "ImageProcessing/PeopleExtractor.h"
#include "../../scene_interface_sma/src/PeopleQueue.hpp"
#include "../../peopleextractor_interface_sma/src/SceneframeQueue.hpp"
#include "../../imove/src/Running.hpp"

// Setups people extractor and Scene, can let the Scene run using constant input of people extractor
class ImovePeopleextractorManager {
	public:
		/**
		 * Setup people extractor and communicate to Scene.
		 * 
		 * @param Calibration The camera projector Calibration
		 **/
		ImovePeopleextractorManager(ImoveConfiguration* calibration);

		// Run the people extractor and Scene frame by frame
		void run();

	protected:
		ImoveConfiguration* calibration;
		Projection projection;
		PeopleExtractor* people_extractor;

		// shared memory segment between extractedpeople and scene
		boost::interprocess::managed_shared_memory* segment;
		// shared memory extracted people queue
		boost::interprocess::offset_ptr<scene_interface_sma::PeopleQueue> si_people_queue;
		// shared memory people extractor scene frame queue
		boost::interprocess::offset_ptr<peopleextractor_interface_sma::SceneframeQueue> pi_sceneframe_queue;
		// shared memory running all processes
		boost::interprocess::offset_ptr<Running> running;
		
		/**
		 * Push extractedpeople on shared memory query for scene to pop.
		 * 
		 * @param people Extracted people for scene input
		 **/
		void sendExtractedpeople(scene_interface::People people);

		// Receive scene frame and feed projection for later projection subtraction
		void receiveSceneFrameAndFeedProjection();
		
		// thread function to receive scene frame and feed projectio for later projection subtraction
		static void receiveSceneFrameAndFeedProjectionThread(ImovePeopleextractorManager* imove_peopleextractor_manager);
};
