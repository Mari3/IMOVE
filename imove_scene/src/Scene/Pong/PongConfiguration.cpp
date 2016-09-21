#include <opencv2/opencv.hpp>
#include "PongConfiguration.h"

PongConfiguration PongConfiguration::readFromFile(char* fileName){
	cv::FileStorage fs;
	fs.open(fileName, cv::FileStorage::READ);

	PongConfiguration res;

	cv::Size resolution;
	fs["Resolution"] >> resolution;
	res.screenWidth = static_cast<unsigned int>(resolution.width);
	res.screenHeight = static_cast<unsigned int>(resolution.height);

	fs["BallSpeed"] >> res.ballSpeed;
	fs["BallThickness"] >> res.bt;
	fs["ControlRange"] >> res.controlRange;
	fs["MaxAngle"] >> res.maxAngle;

	return res;
}
