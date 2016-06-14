#include <opencv2/opencv.hpp>

#include "../../../imove_imp/src/OpenCVUtil.hpp"
#include "DetectedPeopleCameraWindow.hpp"
#include "../../../scene_interface/src/People.h"

DetectedPeopleCameraWindow::DetectedPeopleCameraWindow(cv::Point2i position) : OpenCVWindow("Detected people on camera", position) { }

void DetectedPeopleCameraWindow::drawImage(cv::Mat& image_camera, scene_interface::People& detectedpeople) {
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

