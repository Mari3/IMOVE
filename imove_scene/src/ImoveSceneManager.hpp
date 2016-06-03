#include <boost/interprocess/offset_ptr.hpp>

#include "Calibration/Calibration.hpp"
#include "Scene/LightTrail/LightTrailConfiguration.h"
#include "Scene/Scene.h"
//#include <scene_interface/ExtractedpeopleQueue.hpp>
#include "../../scene_interface/src/ExtractedpeopleQueue.hpp"

// Setups people extractor and Scene, can let the Scene run using constant input of people extractor
class ImoveSceneManager {
	public:
		/**
		 * Setup people extractor and Scene.
		 * 
		 * @param Calibration              The camera projector Calibration
		 * @param configuration_lighttrail The light trail Scene configuration
		 **/
		ImoveSceneManager(Calibration* calibration, LightTrailConfiguration& configuration_lighttrail);

		// Run the people extractor and Scene frame by frame
		void run();

	protected:
		Calibration* calibration;
		Scene* scene = NULL;
		
		// shared memory segment
		boost::interprocess::managed_shared_memory* segment;
		// People extractor queue
		boost::interprocess::offset_ptr<scene_interface::ExtractedpeopleQueue> extractedpeople_queue;
		
		/**
		 * Receive extracted people from people extractor in shared memory queue and update scene
		 **/
		void receiveExtractedpeopleAndUpdateScene();
};
