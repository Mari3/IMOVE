#include "calibration/Calibration.hpp"
#include "scene/LightTrail/LightTrailConfiguration.h"
#include "image_processing/PeopleExtractor.h"
#include "scene/Scene.h"

// Setups people extractor and scene, can let the scene run using constant input of people extractor
class ImoveManager {
	public:
		/**
		 * Setup people extractor and scene.
		 * 
		 * @param calibration              The camera projector calibration
		 * @param configuration_lighttrail The light trail scene configuration
		 **/
		ImoveManager(Calibration* calibration, LightTrailConfiguration& configuration_lighttrail);

		// Run the people extractor and scene frame by frame
		void run();

	protected:
		Calibration* calibration;
		PeopleExtractor* people_extractor;
		Scene* scene = NULL;
};
