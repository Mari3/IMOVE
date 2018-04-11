#include <boost/interprocess/offset_ptr.hpp>


#include "../../util/src/configuration/ImoveConfiguration.hpp"
#include "../../util/src/Projection.hpp"
#include "Scene/LightTrail/Configuration/LightTrailSceneConfiguration.h"
#include "Scene/Scene.h"
#include "Scene/SceneConfiguration.h"
#include "../../scene_interface_sma/src/PeopleQueue.hpp"
#include "../../peopleextractor_interface_sma/src/SceneframeQueue.hpp"
#include "../../imove/src/Running.hpp"

// Setups people extractor and Scene, can let the Scene run using constant input of people extractor
class ImoveSceneManager {
	public:
		/**
		 * Setup people extractor and Scene.
		 *
		 * @param calibration              The imove configuration
		 * @param configuration_lighttrail The light trail Scene configuration
		 **/
		ImoveSceneManager(ImoveConfiguration* calibration, const SceneConfiguration& sceneConfig);

		// Run the people extractor and Scene frame by frame
		void run();

	protected:
		ImoveConfiguration* calibration;
		Projection projection;
		Scene* scene = NULL;

		std::queue<sf::Image> sceneframe_queue;

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

		static void sendingSceneFrameThread(ImoveSceneManager* imove_scene_manager);

		/**
		 * Send scene frame to people extractor via shared memory queue
		 **/
		void sendingSceneFrame();
};
