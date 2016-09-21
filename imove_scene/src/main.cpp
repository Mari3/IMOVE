#include <iostream>
#include <string>

#include "ImoveSceneManager.hpp"
#include "Scene/Pong/PongConfiguration.h"
#include "../../util/src/configuration/ImoveConfiguration.hpp"

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
  
	const PongConfiguration configuration_pong = PongConfiguration::readFromFile(argv[CONFIGURATION_LIGHTTRAIL_ARGN]);

	ImoveSceneManager manager(calibration, configuration_pong);
	manager.run();
	
	return EXIT_SUCCESS;
}
