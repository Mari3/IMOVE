#include <iostream>
#include <string>

#include "ImoveSceneManager.hpp"
#include "Scene/SceneConfiguration.h"

const unsigned int CONFIGURATION_CALIBRATION_ARGN = 1;
const unsigned int CONFIGURATION_LIGHTTRAIL_ARGN = 2;

// setup and run Scene with continous people extraction as input based on configuration given in parameter otherwise show parameters
int main(int argc, char* argv[]) {
	// show parameters if not given 2 parameter
	if (argc != 3) {
		std::cerr << "Usage: <path to configuration file> <path to configuration Scene>" << std::endl;
		return EXIT_SUCCESS;
	}

	ImoveConfiguration* calibration = ImoveConfiguration::readFile(argv[CONFIGURATION_CALIBRATION_ARGN]);

	const SceneConfiguration configuration = SceneConfiguration::readFromFile(argv[CONFIGURATION_LIGHTTRAIL_ARGN], calibration);

	ImoveSceneManager manager(calibration, configuration);
	manager.run();

	return EXIT_SUCCESS;
}
