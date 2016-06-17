#include <iostream>
#include <string>

#include "CalibrationManager.hpp"
#include "../../util/src/configuration/ImoveConfiguration.hpp"


// arguments
unsigned int CONFIGPATH_ARGN = 1;
unsigned int CAMERADEVICE_ARGN = 2;
unsigned int WIDTH_RESOLUTION_ARGN = 3;
unsigned int HEIGHT_RESOLUTION_ARGN = 4;


// create Calibration configuration based on arguments and configuration and user input in projection, meter and projection elimination windows
int main(int argc, char* argv[]) {
	if (argc != 5) {
		std::cout << "Usage: <path to configuration file> <int camera device> <resolution projector width> <resolution projector height>" << std::endl;
		return EXIT_SUCCESS;
	}

	const char* configurationfilepath_calibration = argv[CONFIGPATH_ARGN];
	
	// read from config if property is not set, use default
	ImoveConfiguration* calibration = ImoveConfiguration::createFromFile(
		configurationfilepath_calibration,
		std::stoi(argv[CAMERADEVICE_ARGN]),
		cv::Size(
			std::stoi(argv[WIDTH_RESOLUTION_ARGN]),
			std::stoi(argv[HEIGHT_RESOLUTION_ARGN])
		)
	);

	// start manager with calibration
	CalibrationManager manager(calibration);
	
	// run calibration interaction
	manager.run();
	
	// write calibrated config
	calibration->writeFile(configurationfilepath_calibration);
	
	return EXIT_SUCCESS;
}
