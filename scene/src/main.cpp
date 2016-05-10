#include <opencv2/opencv.hpp>
#include <opencv2/core/persistence.hpp>

#include <iostream>
#include <vector>
#include <string>

#include "Calibration.hpp"

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cout << "Usage: <path to configuration file> <path to camera frame (image)>" << std::endl;
		return 0;
	}

	cv::FileStorage fs;
	fs.open(argv[1], cv::FileStorage::READ);
	cv::Size resolution_projector;
	fs["Resolution_projector"] >> resolution_projector;
	cv::Mat camera_projector_transformation;
	fs["Camera_projector_transformation"] >> camera_projector_transformation;
	fs.release();
 
	cv::Mat camera_frame = cv::imread(argv[2], 1);
	if (camera_frame.empty()) {
		std::cerr << "Camera frame not read correctly!" << std::endl;
		return -1;
	}

	const Calibration calibration = Calibration(resolution_projector, camera_projector_transformation);
	cv::Mat projector_camera_frame;
	calibration.createProjectorCameraFrameFromCameraFrame(projector_camera_frame, camera_frame);
	
	std::vector<cv::Point2f> points_camera_frame(1);
	srand(time(0));
	points_camera_frame[0] = cv::Point2f(
		((float) std::rand()) / ((float) RAND_MAX) * ((float) camera_frame.size().width),
		((float) std::rand()) / ((float) RAND_MAX) * ((float) camera_frame.size().height)
	);
	std::vector<cv::Point2f> points_projector_frame;
	calibration.createPointsProjectorFrameFromPointsCameraFrame(points_projector_frame, points_camera_frame);
	
	circle(
		camera_frame,
		points_camera_frame[0],
		8.f,
		cv::Scalar(0, 0, 255),
		2.f
	);
	circle(
		projector_camera_frame,
		points_projector_frame[0],
		8.f,
		cv::Scalar(0, 0, 255),
		2.f
	);
	
	cv::namedWindow("Camera view", 1);
	cv::moveWindow("Camera view", 0, 0);
	cv::imshow("Camera view", camera_frame);

	cv::namedWindow("Projector camera view", 1);
	cv::moveWindow("Projector camera view", camera_frame.size().width, 0);
	cv::imshow("Projector camera view", projector_camera_frame);

	cv::waitKey(0);
 
	return 0;
}
