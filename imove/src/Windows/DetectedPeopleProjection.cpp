#include <opencv2/opencv.hpp>

#include "../OpenCVUtil.hpp"
#include "DetectedPeopleProjection.hpp"

DetectedPeopleProjectionWindow::DetectedPeopleProjectionWindow(cv::Point2i position) : OpenCVWindow("Detected people on projection", position) { }

void DetectedPeopleProjectionWindow::drawImage(cv::Mat& image_projection, vector<Person>& detectedpeople_projection) {
	// debug extracted perspective mapped people on projection
	for (unsigned int i = 0; i < detectedpeople_projection.size(); ++i) {
		Person detectedperson = detectedpeople_projection.at(i);
		Vector2 vector2_location_detectedperson = detectedperson.getLocation();
		cv::Point2f cv_location_detectedperson = cv::Point2f(
			vector2_location_detectedperson.x,
			vector2_location_detectedperson.y
		);
		cv::circle(
			image_projection,
			cv_location_detectedperson,
			DetectedPeopleProjectionWindow::SIZE_CIRCLE_PROJECTION_DEBUG,
			OpenCVUtil::Color::LIGHTBLUE,
			DetectedPeopleProjectionWindow::THICKNESS_CIRCLE_PROJECTION_DEBUG
		);
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

