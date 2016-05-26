#include <opencv2/highgui/highgui.hpp>

#include <functional>

#include "./CalibrationMeter.hpp"


CalibrationMeterWindow::CalibrationMeterWindow(cv::Point2i position, Calibration* calibration, float meter) : OpenCVWindow("Calibrate meter", position) {
	this->calibration = calibration;
	this->a_meter = cv::Point2f(10, 10);
	this->b_meter = cv::Point2f(10 + meter, 10);
	cv::setMouseCallback(this->name_window, CalibrationMeterWindow::onMouse, (void*) &*this);
}

// Calibrate projection mouse callback
void CalibrationMeterWindow::onMouse(int event, int x, int y, int flags, void* param) {
	CalibrationMeterWindow* that = (CalibrationMeterWindow*) param;
	that->onMouse(event, x, y, flags);
}

void CalibrationMeterWindow::onMouse(int event, int x, int y, int flags) {
	this->coordinate_mouse = cv::Point2f(x, y);
	this->entered_mouse = true;

	if (event == cv::EVENT_LBUTTONUP) {
		switch (this->current_meter) {
			case METER::A:
				// set meter first position and set right as current position
				this->a_meter = this->coordinate_mouse;
				this->current_meter = METER::B;
				break;
			case METER::B:
				// set meter second position and set left as current position
				this->b_meter = this->coordinate_mouse;
				this->current_meter = METER::A;
				break;
		}
	}
}

void CalibrationMeterWindow::drawImage(cv::Mat image) {
	// draw line between first and second point
	cv::line(image, this->a_meter, this->b_meter, cv::Scalar(255, 255, 255));
	// draw meter cross first point
	OpenCVUtil::drawCrossOnImage(image, this->a_meter, this->COLOR_A_METER, this->SIZE_CROSS, this->THICKNESS_CROSS);
	// draw meter cross second point
	OpenCVUtil::drawCrossOnImage(image, this->b_meter, this->COLOR_B_METER, this->SIZE_CROSS, this->THICKNESS_CROSS);
	// draw last mouse position as current setting meter point if ever entered
	if (this->entered_mouse) {
		switch (this->current_meter) {
			case METER::A:
				OpenCVUtil::drawCrossOnImage(image, this->coordinate_mouse, this->COLOR_A_METER, SIZE_CROSS, THICKNESS_CROSS);
				break;
			case METER::B:
				OpenCVUtil::drawCrossOnImage(image, this->coordinate_mouse, this->COLOR_B_METER, SIZE_CROSS, THICKNESS_CROSS);
				break;
		}
	}

	OpenCVWindow::drawImage(image);
}

float CalibrationMeterWindow::getMeter() const {
	cv::Point2f diff_meter = this->b_meter - a_meter;
	return sqrt(abs(diff_meter.x * diff_meter.x + diff_meter.y * diff_meter.y));
}
