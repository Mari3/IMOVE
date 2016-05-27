#include <opencv2/core/persistence.hpp>

#include <iostream>
#include <vector>
#include <string>

#include "Manager.hpp"
#include "calibration/Calibration.hpp"

const unsigned int CONFIGURATION_CALIBRATION_ARGN = 1;
const unsigned int CONFIGURATION_LIGHTTRAIL_ARGN = 2;

// setup and run scene with continous people extraction as input based on configuration given in parameter otherwise show parameters
int main(int argc, char* argv[]) {
	// show parameters if not given 1 parameter
	if (argc != 3) {
		std::cerr << "Usage: <path to configuration file> <path to configuration scene>" << std::endl;
		return EXIT_SUCCESS;
	}

	Calibration* calibration = Calibration::loadFromFile(argv[CONFIGURATION_CALIBRATION_ARGN]);
  
	LightTrailConfiguration configuration_lighttrail = LightTrailConfiguration::readFromFile(argv[CONFIGURATION_LIGHTTRAIL_ARGN]);

	Manager manager(calibration, configuration_lighttrail);
	if (manager.run()) {
		return EXIT_SUCCESS;
	} else {
		std::cerr << "Exiting due to unexpected run error." << std::endl;
		return EXIT_FAILURE;
	}
}
