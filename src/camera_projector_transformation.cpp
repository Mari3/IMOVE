#include "opencv2/highgui/highgui.hpp"
 
#include <iostream>
#include <string>

#include "findCameraProjectorTransformation.hpp"
 
int main(int argc, char* argv[]) {
	const cv::Size size_checkerboard(9, 6); //todo config

	if (argc != 3) {
		std::cout << "Usage: <path to camera frame (image)> <path to projector frame (image)>";
		return 0;
	}
 
	cv::Mat camera_frame = cv::imread(argv[1], 1);
	cv::Mat projector_frame = cv::imread(argv[2], 1);
	if (camera_frame.empty()) {
		std::cerr << "Camera frame not read correctly!" << std::endl;
		return -1;
	}
	if (projector_frame.empty()) {
		std::cerr << "Projector frame not read correctly!" << std::endl;
		return -1;
	}

	const cv::Mat camera_projector_transformation = findCameraProjectorTransformationFromCheckerboard(camera_frame, projector_frame, size_checkerboard);

	cv::Mat derived_projector_frame;
	cv::warpPerspective(
		camera_frame,
		derived_projector_frame,
		camera_projector_transformation,
		projector_frame.size()
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
	
	cv::namedWindow("Projector view", 1);
	cv::moveWindow("Projector view", camera_frame.size().width + derived_projector_frame.size().width, 0);
	cv::imshow("Projector view", derived_projector_frame);

	cv::waitKey(0);
 
	return 0;
}
