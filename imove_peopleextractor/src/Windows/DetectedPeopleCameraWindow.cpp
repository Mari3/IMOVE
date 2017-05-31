#include <opencv2/opencv.hpp>

#include "../../../util/src/OpenCVUtil.hpp"
#include "DetectedPeopleCameraWindow.hpp"
#include "../../../scene_interface/src/People.h"

DetectedPeopleCameraWindow::DetectedPeopleCameraWindow(cv::Point2i position, cv::Size size) : OpenCVWindow("Detected people on camera", position, size) { }

void DetectedPeopleCameraWindow::drawImage(cv::Mat& image_camera, scene_interface::People& detectedpeople) {

	float scale = 2.2222;

	float ULxa = 50.65*scale;
	float ULy = 50.4*scale;
	float ULxb = 90.65*scale;
	float LLxa = 46.15*scale;
	float LLy = 135.45*scale;
	float LLxb = 86.15*scale;

	float URxb = 200.95*scale;
	float URy = 54.45*scale;
	float URxa = 240.95*scale;
	float LRxb = 202.75*scale;
	float LRy = 139.05*scale;
	float LRxa = 242.75*scale;

	cv::line(image_camera, cv::Point2f(ULxa, ULy), cv::Point2f(ULxb, ULy), cv::Scalar(200, 100, 50));
	cv::line(image_camera, cv::Point2f(ULxb, ULy), cv::Point2f(LLxb, LLy), cv::Scalar(200, 100, 50));
	cv::line(image_camera, cv::Point2f(LLxb, LLy), cv::Point2f(LLxa, LLy), cv::Scalar(200, 100, 50));
	cv::line(image_camera, cv::Point2f(LLxa, LLy), cv::Point2f(ULxa, ULy), cv::Scalar(200, 100, 50));

	cv::line(image_camera, cv::Point2f(URxb, URy), cv::Point2f(URxa, URy), cv::Scalar(50, 100, 200));
	cv::line(image_camera, cv::Point2f(URxb, URy), cv::Point2f(LRxb, LRy), cv::Scalar(50, 100, 200));
	cv::line(image_camera, cv::Point2f(LRxa, LRy), cv::Point2f(URxa, URy), cv::Scalar(50, 100, 200));
	cv::line(image_camera, cv::Point2f(LRxa, LRy), cv::Point2f(LRxb, LRy), cv::Scalar(50, 100, 200));


	// debug people drawing on camera frame
	for (unsigned int i = 0; i < detectedpeople.size(); ++i) {
		scene_interface::Location location_detectedperson = detectedpeople.at(i).getLocation();
		// draw circle on each detected person location
		cv::circle(
			image_camera,
			cv::Point2f(
				location_detectedperson.getX(),
				location_detectedperson.getY()
			),
			DetectedPeopleCameraWindow::SIZE_CIRCLE_CAMERA_DEBUG,
			OpenCVUtil::Color::DARKBLUE,
			DetectedPeopleCameraWindow::THICKNESS_CIRCLE_CAMERA_DEBUG
		);
	}

	OpenCVWindow::drawImage(image_camera);
}
