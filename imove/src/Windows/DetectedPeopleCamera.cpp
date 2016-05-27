#include <opencv2/opencv.hpp>

#include "../OpenCVUtil.hpp"
#include "DetectedPeopleCamera.hpp"

DetectedPeopleCameraWindow::DetectedPeopleCameraWindow(cv::Point2i position) : OpenCVWindow("Detected people on camera", position) { }

void DetectedPeopleCameraWindow::drawImage(cv::Mat& image_camera, vector<Person>& detectedpeople) {
	// debug people drawing on camera frame
	for (unsigned int i = 0; i < detectedpeople.size(); ++i) {
		Vector2 location_detectedperson = detectedpeople.at(i).getLocation();
		cv::circle(
			image_camera,
			cv::Point2f(
				location_detectedperson.x,
				location_detectedperson.y
			),
			DetectedPeopleCameraWindow::SIZE_CIRCLE_CAMERA_DEBUG,
			OpenCVUtil::Color::DARKBLUE,
			DetectedPeopleCameraWindow::THICKNESS_CIRCLE_CAMERA_DEBUG
		);
	}
	
	OpenCVWindow::drawImage(image_camera);
}

