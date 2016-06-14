#include <opencv2/opencv.hpp>

#include "../../../imove_imp/src/OpenCVUtil.hpp"
#include "DetectedPeopleProjectionWindow.hpp"

DetectedPeopleProjectionWindow::DetectedPeopleProjectionWindow(cv::Point2i position) : OpenCVWindow("Detected people on projection", position) { }

void DetectedPeopleProjectionWindow::drawImage(cv::Mat& image_projection, const scene_interface::People& detectedpeople_projection) {
	// debug extracted perspective mapped people on projection
	for (unsigned int i = 0; i < detectedpeople_projection.size(); ++i) {
		scene_interface::Person detectedperson = detectedpeople_projection.at(i);
		scene_interface::Location vector2_location_detectedperson = detectedperson.getLocation();
		// opencv point on location detected person
		cv::Point2f cv_location_detectedperson = cv::Point2f(
			vector2_location_detectedperson.getX(),
			vector2_location_detectedperson.getY()
		);
		// draw circle around detected person location
		cv::circle(
			image_projection,
			cv_location_detectedperson,
			DetectedPeopleProjectionWindow::SIZE_CIRCLE_PROJECTION_DEBUG,
			OpenCVUtil::Color::LIGHTBLUE,
			DetectedPeopleProjectionWindow::THICKNESS_CIRCLE_PROJECTION_DEBUG
		);
		// put id text at detected person location
		cv::putText(
			image_projection,
			std::to_string(detectedperson.getId()),
			cv_location_detectedperson,
			cv::FONT_HERSHEY_SIMPLEX,
			DetectedPeopleProjectionWindow::SIZE_FONT_DEBUG,
			OpenCVUtil::Color::DARKBLUE
		);
	}

	OpenCVWindow::drawImage(image_projection);
}

