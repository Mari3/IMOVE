#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Calibration.hpp"

Calibration::Calibration(cv::Size& resolution_projector, cv::Mat& camera_projector_transformation) {
	this->resolution_projector = resolution_projector;
	this->camera_projector_transformation = camera_projector_transformation;
}

void Calibration::createPointsProjectorFrameFromPointsCameraFrame(std::vector<cv::Point2f>& points_projector_frame, const std::vector<cv::Point2f>& points_camera_frame) const {
	cv::perspectiveTransform(
		points_camera_frame,
		points_projector_frame,
		this->camera_projector_transformation
	);
}

void Calibration::createProjectionFrameFromCameraFrame(cv::Mat& projection_frame, const cv::Mat& camera_frame) const {
	cv::warpPerspective(
		camera_frame,
		projection_frame,
		this->camera_projector_transformation,
		this->resolution_projector
	);
}
