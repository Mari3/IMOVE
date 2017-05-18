#include <opencv2/opencv.hpp>

#include "../../../util/src/OpenCVUtil.hpp"
#include "DetectedPeopleCameraWindow.hpp"
#include "../../../scene_interface/src/People.h"

DetectedPeopleCameraWindow::DetectedPeopleCameraWindow(cv::Point2i position, cv::Size size) : OpenCVWindow("Detected people on camera", position, size) { }

void DetectedPeopleCameraWindow::drawImage(cv::Mat& image_camera, scene_interface::People& detectedpeople) {

	cv::line(image_camera, cv::Point2f(57.4*2.2222, 78.75*2.2222), cv::Point2f(97.4*2.2222, 78.75*2.2222), cv::Scalar(200, 100, 50));
	cv::line(image_camera, cv::Point2f(97.4*2.2222, 78.75*2.2222), cv::Point2f(91.55*2.2222, 166.55*2.2222), cv::Scalar(200, 100, 50));
	cv::line(image_camera, cv::Point2f(91.55*2.2222, 166.55*2.2222), cv::Point2f(51.55*2.2222, 166.55*2.2222), cv::Scalar(200, 100, 50));
	cv::line(image_camera, cv::Point2f(51.55*2.2222, 166.55*2.2222), cv::Point2f(57.4*2.2222, 78.75*2.2222), cv::Scalar(200, 100, 50));

	cv::line(image_camera, cv::Point2f(193.3*2.2222, 82.35*2.2222), cv::Point2f(233.3*2.2222, 82.35*2.2222), cv::Scalar(50, 100, 200));
	cv::line(image_camera, cv::Point2f(193.3*2.2222, 82.35*2.2222), cv::Point2f(195.55*2.2222, 169.65*2.2222), cv::Scalar(50, 100, 200));
	cv::line(image_camera, cv::Point2f(235.55*2.2222, 169.65*2.2222), cv::Point2f(233.3*2.2222, 82.35*2.2222), cv::Scalar(50, 100, 200));
	cv::line(image_camera, cv::Point2f(235.55*2.2222, 169.65*2.2222), cv::Point2f(195.55*2.2222, 169.65*2.2222), cv::Scalar(50, 100, 200));


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
