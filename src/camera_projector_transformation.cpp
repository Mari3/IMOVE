#include "opencv2/highgui/highgui.hpp"
 
#include <iostream>
#include <string>

#include "findCameraProjectorTransformation.hpp"
 
int main(int argc, char* argv[]) {
	if (argc != 6) {
		std::cout << "Usage: <path to camera frame (image)> <projector resolution width> <projector resolution height> <chessboard corners width> <chessboard corners height>" << std::endl;
		return 0;
	}
 
	cv::Mat camera_frame = cv::imread(argv[1], 1);
	if (camera_frame.empty()) {
		std::cerr << "Camera frame not read correctly!" << std::endl;
		return -1;
	}
	const cv::Size resolution_projector(std::stoi(argv[2]), std::stoi(argv[3]));
	const cv::Size size_checkerboard(std::stoi(argv[4]), std::stoi(argv[5]));
std::cout << "a" << size_checkerboard << "b" << resolution_projector << std::endl;

	const cv::Mat camera_projector_transformation = findCameraProjectorTransformationFromCheckerboard(camera_frame, resolution_projector, size_checkerboard);

	cv::Mat derived_projector_frame;
	cv::warpPerspective(
		camera_frame,
		derived_projector_frame,
		camera_projector_transformation,
		resolution_projector
	);
	
	std::vector<cv::Point2f> points_camera_frame(1);
	points_camera_frame[0] = cv::Point2f(
		std::rand() * camera_frame.size().width,
		std::rand() * camera_frame.size().height
	);
	std::vector<cv::Point2f> points_projector_frame;
	cv::perspectiveTransform(
		points_camera_frame,
		points_projector_frame,
		camera_projector_transformation
	);
	
	cv::namedWindow("Camera view", 1);
	cv::moveWindow("Camera view", 0, 0);
	cv::imshow("Camera view", camera_frame);

	cv::namedWindow("Derived projector view", 1);
	cv::moveWindow("Derived projector view", camera_frame.size().width, 0);
	cv::imshow("Derived projector view", derived_projector_frame);

	cv::waitKey(0);
 
	return 0;
}
