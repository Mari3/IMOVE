#include <iostream>
#include <string>

#include "ImovePeopleextractorManager.hpp"
#include "../../util/src/configuration/ImoveConfiguration.hpp"
#include "../../util/src/Projection.hpp"

const unsigned int CONFIGURATION_CALIBRATION_ARGN = 1;

// setup and run Scene with continous people extraction as input based on configuration given in parameter otherwise show parameters
int main(int argc, char* argv[]) {
	// show parameters if not given 1 parameter
	if (argc != 2) {
		std::cerr << "Usage: <path to configuration file>" << std::endl;
		return EXIT_SUCCESS;
	}
	ImoveConfiguration* calibration = ImoveConfiguration::readFile(argv[CONFIGURATION_CALIBRATION_ARGN]);

	ImovePeopleextractorManager manager(calibration);
	manager.run();
	
	return EXIT_SUCCESS;
}
