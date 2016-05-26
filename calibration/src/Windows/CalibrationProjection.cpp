#include <opencv2/highgui/highgui.hpp>

#include <functional>

#include "../OpenCVUtil.hpp"
#include "./CalibrationProjection.hpp"


CalibrationProjectionWindow::CalibrationProjectionWindow(cv::Point2i position, Calibration* calibration, cv::Size resolution_projector) : OpenCVWindow("Calibrate projection", position) {
	this->calibration = calibration;
	// set ui color of corners
	this->color_corners[0] = OpenCVUtil::Color::ORANGE;
	this->color_corners[1] = OpenCVUtil::Color::GREEN;
	this->color_corners[2] = OpenCVUtil::Color::DARKBLUE;
	this->color_corners[3] = OpenCVUtil::Color::LIGHTBLUE;
	// set projector coordinates
	coordinate_corners_projector[0] = cv::Point2f(        OpenCVUtil::ORIGIN2D.x,          OpenCVUtil::ORIGIN2D.y);
	coordinate_corners_projector[1] = cv::Point2f(resolution_projector.width - 1,          OpenCVUtil::ORIGIN2D.y);
	coordinate_corners_projector[2] = cv::Point2f(        OpenCVUtil::ORIGIN2D.x, resolution_projector.height - 1);
	coordinate_corners_projector[3] = cv::Point2f(resolution_projector.width - 1, resolution_projector.height - 1);
	
	// reconstruct points camera from projector points and perspective transformation
	std::vector<cv::Point2f> points_projector = std::vector<cv::Point2f>(this->CalibrationProjectionWindow::REQUIRED_CORNERS);
	points_projector.at(0) = coordinate_corners_projector[0];
	points_projector.at(1) = coordinate_corners_projector[1];
	points_projector.at(2) = coordinate_corners_projector[2];
	points_projector.at(3) = coordinate_corners_projector[3];
	std::vector<cv::Point2f> points_projection = std::vector<cv::Point2f>(CalibrationProjectionWindow::REQUIRED_CORNERS);
	cv::perspectiveTransform(
		points_projector,
		points_projection,
		calibration->getCameraProjectorTransformation().inv()
	);
	coordinate_corners_camera[0] = points_projection.at(0);
	coordinate_corners_camera[1] = points_projection.at(1);
	coordinate_corners_camera[2] = points_projection.at(2);
	coordinate_corners_camera[3] = points_projection.at(3);
	
	cv::setMouseCallback(this->name_window, CalibrationProjectionWindow::onMouse, (void*) &*this);
}

// Calibrate projection mouse callback
void CalibrationProjectionWindow::onMouse(int event, int x, int y, int flags, void* param) {
	CalibrationProjectionWindow* that = (CalibrationProjectionWindow*) param;
	that->onMouse(event, x, y, flags);
}
void CalibrationProjectionWindow::onMouse(int event, int x, int y, int flags) {
	this->coordinate_mouse_projection = cv::Point2f(x, y);
	this->entered_mouse_projection = true;

	if (event == cv::EVENT_LBUTTONUP) {
		// set new corner based on last mouse position
		this->coordinate_corners_camera[this->current_corner] = this->coordinate_mouse_projection;
		// set new current corner to set
		this->current_corner = (this->current_corner + 1) % this->CalibrationProjectionWindow::REQUIRED_CORNERS;
		// calculate and set new perspective map
		cv::Mat camera_projector_transformation = cv::getPerspectiveTransform(
			this->coordinate_corners_camera,
			this->coordinate_corners_projector
		);
		this->calibration->setCameraProjectorTransformation(camera_projector_transformation);
	}
}

/**
 * Draws projection boundaries on image as polylines between corners, draw crosses on corners and draw last mouse position
 **/
void CalibrationProjectionWindow::drawImage(cv::Mat image) {
	// draw polylines on this->frame to indicate boundaries
	cv::Point polypoints[this->CalibrationProjectionWindow::REQUIRED_CORNERS];
	polypoints[0] = this->coordinate_corners_camera[0];
	polypoints[1] = this->coordinate_corners_camera[1];
	polypoints[2] = this->coordinate_corners_camera[3];
	polypoints[3] = this->coordinate_corners_camera[2];
	const cv::Point* ppt[1] = { polypoints };
	int npt[] = {this->CalibrationProjectionWindow::REQUIRED_CORNERS};
	cv::polylines(
		image,
		ppt,
		npt,
		1,
		true,
		OpenCVUtil::Color::WHITE,
		this->THICKNESS_LINE,
		cv::LINE_AA
	);

	// draw cross on corner projection boundaries
	for (unsigned int i = 0; i < CalibrationProjectionWindow::REQUIRED_CORNERS; ++i) {
		OpenCVUtil::drawCrossOnImage(
			image,
			this->coordinate_corners_camera[i],
			this->color_corners[i],
			this->SIZE_CROSS,
			this->THICKNESS_CROSS
		);
	}
	
	// draw mouse on image if ever entered
	if (this->entered_mouse_projection) {
		OpenCVUtil::drawCrossOnImage(
			image,
			this->coordinate_mouse_projection,
			this->color_corners[this->current_corner],
			this->SIZE_CROSS,
			this->THICKNESS_CROSS
		);
	}
	
	OpenCVWindow::drawImage(image);
}

