#include <boost/interprocess/offset_ptr.hpp>


#include "../../imove_imp/src/Calibration.hpp"
#include "Scene/LightTrail/Configuration/LightTrailSceneConfiguration.h"
#include "Scene/Scene.h"
#include "../../scene_interface_sma/src/PeopleQueue.hpp"
#include "../../peopleextractor_interface_sma/src/SceneframeQueue.hpp"
#include "../../imove/src/Running.hpp"

// Setups people extractor and Scene, can let the Scene run using constant input of people extractor
class ImoveSceneManager {
	public:
		/**
		 * Setup people extractor and Scene.
		 * 
		 * @param Calibration              The camera projector Calibration
		 * @param configuration_lighttrail The light trail Scene configuration
		 **/
		ImoveSceneManager(Calibration* calibration, LightTrailSceneConfiguration& configuration_lighttrail);

		// Run the people extractor and Scene frame by frame
		void run();

	protected:
		Calibration* calibration;
		Scene* scene = NULL;
		
		// shared memory segment
		boost::interprocess::managed_shared_memory* segment;
		// People extractor queue
		boost::interprocess::offset_ptr<scene_interface_sma::PeopleQueue> si_people_queue;
		// Scene frames queue
		boost::interprocess::offset_ptr<peopleextractor_interface_sma::SceneframeQueue> pi_sceneframe_queue;
		// whole application running
		boost::interprocess::offset_ptr<Running> running;
		
		/**
		 * Receive extracted people from people extractor in shared memory queue and update scene
		 **/
		void receiveExtractedpeopleAndUpdateScene();

		static void sendSceneFrameThread(ImoveSceneManager* imove_scene_manager, sf::Image sf_image);
		
		/**
		 * Send scene frame to people extractor via shared memory queue
		 **/
		void sendSceneFrame(const sf::Image& frame_scene);
};
