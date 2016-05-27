#include <SFML/Graphics.hpp>

#include "calibration/Calibration.hpp"
#include "scene/LightTrail/LightTrailConfiguration.h"
#include "image_processing/PeopleExtractor.h"
#include "scene/Scene.h"


class ImoveManager {
	public:
		ImoveManager(Calibration* calibration, LightTrailConfiguration configuration_lighttrail);

		bool run();

	protected:
		Calibration* calibration;
		
		PeopleExtractor* people_extractor;
		int camera_device;

		Scene* scene = NULL;
		sf::RenderWindow* window_scene;
};
