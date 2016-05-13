#include <opencv2/opencv.hpp>
#include <opencv2/core/persistence.hpp>

#include <iostream>
#include <vector>
#include <string>

#include "Calibration.hpp"

const unsigned char U8_WHITE = 255;
const signed int NOKEY_ANYKEY = -1;

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cout << "Usage: <path to configuration file> <int video device>" << std::endl;
		return EXIT_SUCCESS;
	}

	cv::FileStorage fs;
	fs.open(argv[1], cv::FileStorage::READ);
	cv::Size resolution_projector;
	fs["Resolution_projector"] >> resolution_projector;
	cv::Mat camera_projector_transformation;
	fs["Camera_projector_transformation"] >> camera_projector_transformation;
	fs.release();

	const Calibration calibration = Calibration(resolution_projector, camera_projector_transformation);
	cv::Mat projection_frame;
	
	cv::Mat projector_frame = cv::Mat::ones(resolution_projector.width, resolution_projector.height, CV_8UC3) * U8_WHITE;
	cv::namedWindow("Projector", cv::WINDOW_NORMAL);
	cv::moveWindow("Projector", 0, 0);
	cv::imshow("Projector", projector_frame);

	cv::Mat frame_camera;
	cv::VideoCapture video_capture(std::stoi(argv[2]));
	cv::namedWindow("Camera", cv::WINDOW_NORMAL);
	cv::moveWindow("Camera", 500, 0);

	cv::namedWindow("Projection", cv::WINDOW_NORMAL);
	cv::moveWindow("Projection", 1000, 0);
	cv::Mat frame_projection;
	while (cv::waitKey(1) == NOKEY_ANYKEY) {
		if (!video_capture.read(frame_camera)) {
			std::cerr << "Unable to read next frame." << std::endl;
			std::cerr << "Exiting..." << std::endl;
			return EXIT_FAILURE;
		}
		cv::imshow("Camera", frame_camera);
		cv::warpPerspective(
			frame_camera,
			frame_projection,
			camera_projector_transformation,
			resolution_projector
		);
		cv::imshow("Projection", frame_projection);
	}
 
	return EXIT_SUCCESS;
}
