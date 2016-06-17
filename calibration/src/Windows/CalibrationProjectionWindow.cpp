#include <opencv2/highgui/highgui.hpp>

#include <functional>

#include "../../../util/src/OpenCVUtil.hpp"
#include "./CalibrationProjectionWindow.hpp"


CalibrationProjectionWindow::CalibrationProjectionWindow(cv::Point2i position, cv::Size size, Calibration& calibration) : OpenCVWindow("Calibrate projection", position, size),
	color_topleft    (OpenCVUtil::Color::ORANGE),
	color_topright   (OpenCVUtil::Color::GREEN),
	color_bottomleft (OpenCVUtil::Color::DARKBLUE),
	color_bottomright(OpenCVUtil::Color::LIGHTBLUE),
	coordinate_topleft    ( calibration.getProjection().getUpperLeft().x,  calibration.getProjection().getUpperLeft().y),
	coordinate_topright   (calibration.getProjection().getUpperRight().x, calibration.getProjection().getUpperRight().y),
	coordinate_bottomleft ( calibration.getProjection().getLowerLeft().x,  calibration.getProjection().getLowerLeft().y),
	coordinate_bottomright(calibration.getProjection().getLowerRight().x, calibration.getProjection().getLowerRight().y),
	calibration(calibration)
{
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
		// set new corner based on last mouse position & set new current corner
		switch (this->current_corner) {
			case TOPLEFT:
				this->current_corner = TOPRIGHT;
				this->coordinate_topleft = coordinate_mouse_projection;
				break;
			case TOPRIGHT:
				this->current_corner = BOTTOMRIGHT;
				this->coordinate_topright = coordinate_mouse_projection;
				break;
			case BOTTOMRIGHT:
				this->current_corner = BOTTOMLEFT;
				this->coordinate_bottomright = coordinate_mouse_projection;
				break;
			case BOTTOMLEFT:
				this->current_corner = TOPLEFT;
				this->coordinate_bottomleft = coordinate_mouse_projection;
				break;
		}

		const Vector2 upperleft = Vector2(coordinate_topleft.x, coordinate_topleft.y);
		const Vector2 upperright = Vector2(coordinate_topright.x, coordinate_topright.y);
		const Vector2 lowerleft = Vector2(coordinate_bottomleft.x, coordinate_bottomleft.y);
		const Vector2 lowerright = Vector2(coordinate_bottomright.x, coordinate_bottomright.y);
		this->calibration.setProjection(Boundary(upperleft, upperright, lowerleft, lowerright));
	}
}

/**
 * Draws projection boundaries on image as polylines between corners, draw crosses on corners and draw last mouse position
 **/
void CalibrationProjectionWindow::drawImage(cv::Mat image) {
	const Boundary& projection = this->calibration.getProjection();
	const unsigned int REQUIRED_CORNERS = 4;
	const Vector2& topleft     = projection.getUpperLeft();
	const Vector2& topright    = projection.getUpperRight();
	const Vector2& bottomleft  = projection.getLowerLeft();
	const Vector2& bottomright = projection.getLowerRight();

	// draw polylines on this->frame to indicate boundaries
	cv::Point polypoints[REQUIRED_CORNERS];
	polypoints[0] = cv::Point2f(    topleft.x,     topleft.y);
	polypoints[1] = cv::Point2f(   topright.x,    topright.y);
	polypoints[2] = cv::Point2f(bottomright.x, bottomright.y);
	polypoints[3] = cv::Point2f( bottomleft.x,  bottomleft.y);
	const cv::Point* ppt[1] = { polypoints };
	int npt[] = {REQUIRED_CORNERS};
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
	OpenCVUtil::drawCrossOnImage(
		image,
		coordinate_topleft,
		color_topleft,
		this->SIZE_CROSS,
		this->THICKNESS_CROSS
	);
	OpenCVUtil::drawCrossOnImage(
		image,
		coordinate_topright,
		color_topright,
		this->SIZE_CROSS,
		this->THICKNESS_CROSS
	);
	OpenCVUtil::drawCrossOnImage(
		image,
		coordinate_bottomleft,
		color_bottomleft,
		this->SIZE_CROSS,
		this->THICKNESS_CROSS
	);
	OpenCVUtil::drawCrossOnImage(
		image,
		coordinate_bottomright,
		color_bottomright,
		this->SIZE_CROSS,
		this->THICKNESS_CROSS
	);

	// draw mouse on image if ever entered
	if (this->entered_mouse_projection) {
		cv::Scalar mouse_cross_color;
		switch (this->current_corner) {
			case TOPLEFT:
				mouse_cross_color = color_topleft / 2;
				break;
			case TOPRIGHT:
				mouse_cross_color = color_topright / 2;
				break;
			case BOTTOMLEFT:
				mouse_cross_color = color_bottomleft / 2;
				break;
			case BOTTOMRIGHT:
				mouse_cross_color = color_bottomright / 2;
				break;
		}
		OpenCVUtil::drawCrossOnImage(
			image,
			this->coordinate_mouse_projection,
			mouse_cross_color,
			this->SIZE_CROSS,
			this->THICKNESS_CROSS
		);
	}

	OpenCVWindow::drawImage(image);
}
