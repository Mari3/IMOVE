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

	// read calibration config
	cv::FileStorage fs;
	fs.open(argv[CONFIGURATION_CALIBRATION_ARGN], cv::FileStorage::READ);
	int camera_device;
	fs["Camera_device"] >> camera_device;
	cv::Size resolution_camera;
	fs["Resolution_camera"] >> resolution_camera;
	cv::Size resolution_projector;
	fs["Resolution_projector"] >> resolution_projector;
	cv::Mat camera_projector_transformation;
	fs["Camera_projector_transformation"] >> camera_projector_transformation;
	unsigned int frames_projector_camera_delay;
	signed int int_frames_projector_camera_delay;
	fs["Frames_projector_camera_delay"] >> int_frames_projector_camera_delay;
	if (int_frames_projector_camera_delay < 0) {
		frames_projector_camera_delay = 0;
	} else {
		frames_projector_camera_delay = (unsigned int) int_frames_projector_camera_delay;
	}
	double percentage_projector_background_light;
	fs["Percentage_projector_background_light"] >> percentage_projector_background_light;
	float meter;
	fs["Meter"] >> meter;
	fs.release();

	Calibration* calibration = new Calibration(resolution_projector, resolution_camera, camera_device, camera_projector_transformation, frames_projector_camera_delay, percentage_projector_background_light, meter);
  
	LightTrailConfiguration configuration_lighttrail = LightTrailConfiguration::readFromFile(argv[CONFIGURATION_LIGHTTRAIL_ARGN]);

	Manager manager(calibration, configuration_lighttrail);
	if (manager.run()) {
		return EXIT_SUCCESS;
	} else {
		std::cerr << "Exiting due to unexpected run error." << std::endl;
		return EXIT_FAILURE;
	}
}
