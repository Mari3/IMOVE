#include <SFML/Graphics.hpp>

#include "calibration/Calibration.hpp"
#include "scene/LightTrail/LightTrailConfiguration.h"
#include "image_processing/PeopleExtractor.h"
#include "scene/Scene.h"


class ImoveManager {
	public:
		// ui debug elements
		const unsigned int SIZE_FONT_DEBUG = 1;
		const unsigned int SIZE_CIRCLE_PROJECTION_DEBUG = 80;
		const unsigned int THICKNESS_CIRCLE_PROJECTION_DEBUG = 8;
		const unsigned int SIZE_CIRCLE_CAMERA_DEBUG = 20;
		const unsigned int THICKNESS_CIRCLE_CAMERA_DEBUG = 2;

		ImoveManager(Calibration* calibration, LightTrailConfiguration configuration_lighttrail);

		bool run();

	protected:
		Calibration* calibration;
		
		PeopleExtractor* people_extractor;
		int camera_device;

		Scene* scene = NULL;
		sf::RenderWindow* window_scene;
};
