#include "calibration/Calibration.hpp"
#include "scene/LightTrail/LightTrailConfiguration.h"
#include "image_processing/PeopleExtractor.h"
#include "scene/Scene.h"


class ImoveManager {
	public:
		ImoveManager(Calibration* calibration, LightTrailConfiguration& configuration_lighttrail);

		void run();

	protected:
		Calibration* calibration;
		PeopleExtractor* people_extractor;
		Scene* scene = NULL;
};
