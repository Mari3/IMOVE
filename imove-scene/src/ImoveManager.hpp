#include "Calibration/Calibration.hpp"
#include "Scene/LightTrail/LightTrailConfiguration.h"
#include "ImageProcessing/PeopleExtractor.h"
#include "Scene/Scene.h"

// Setups people extractor and Scene, can let the Scene run using constant input of people extractor
class ImoveManager {
	public:
		/**
		 * Setup people extractor and Scene.
		 * 
		 * @param Calibration              The camera projector Calibration
		 * @param configuration_lighttrail The light trail Scene configuration
		 **/
		ImoveManager(Calibration* calibration, LightTrailConfiguration& configuration_lighttrail);

		// Run the people extractor and Scene frame by frame
		void run();

	protected:
		Calibration* calibration;
		PeopleExtractor* people_extractor;
		Scene* scene = NULL;
};
