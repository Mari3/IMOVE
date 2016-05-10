#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/persistence.hpp>
 
#include <iostream>
#include <string>

#include "findCameraProjectorTransformation.hpp"
 
int main(int argc, char* argv[]) {
	if (argc != 7) {
		std::cout << "Usage: <path to configuration file> <path to calibration camera frame (image)> <projector resolution width> <projector resolution height> <chessboard corners width> <chessboard corners height>" << std::endl;
		return 0;
	}
 
	cv::Mat calibration_camera_frame = cv::imread(argv[2], 1);
	if (calibration_camera_frame.empty()) {
		std::cerr << "Calibration camera frame not read correctly!" << std::endl;
		return -1;
	}
	const cv::Size resolution_projector(std::stoi(argv[3]), std::stoi(argv[4]));
	const cv::Size size_checkerboard(std::stoi(argv[5]), std::stoi(argv[6]));
	
	const cv::Mat camera_projector_transformation = findCameraProjectorTransformationFromCheckerboard(calibration_camera_frame, resolution_projector, size_checkerboard);

	cv::FileStorage fs(argv[1], cv::FileStorage::WRITE);
	fs << "Resolution_projector" << resolution_projector;
	fs << "Camera_projector_transformation" << camera_projector_transformation;
	fs.release();
}
