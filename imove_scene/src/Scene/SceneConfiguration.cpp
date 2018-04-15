#include <opencv2/opencv.hpp>
#include "SceneConfiguration.h"

SceneConfiguration SceneConfiguration::readFromFile(char* fileName, ImoveConfiguration* calibration){
	cv::FileStorage fs;
	// Open file
	fs.open(fileName, cv::FileStorage::READ);

	SceneConfiguration config;

	// Read and store resolution of the scene
	cv::Size resolution = calibration->getProjectorConfiguration()->getResolution();
	config.screenWidth = static_cast<unsigned int>(resolution.width);
	config.screenHeight = static_cast<unsigned int>(resolution.height);

	// Read and store circle radius
	fs["Radius"] >> config.radius;

	// Return the configuration
	return config;
}
