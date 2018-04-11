#include <opencv2/opencv.hpp>
#include "SceneConfiguration.h"

SceneConfiguration SceneConfiguration::readFromFile(char* fileName){
	cv::FileStorage fs;
	fs.open(fileName, cv::FileStorage::READ);

	SceneConfiguration config;

	cv::Size resolution;
	fs["Resolution"] >> resolution;
	config.screenWidth = static_cast<unsigned int>(resolution.width);
	config.screenHeight = static_cast<unsigned int>(resolution.height);

	fs["Radius"] >> config.radius;

	return config;
}
