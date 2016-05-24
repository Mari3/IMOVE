#include "./ProjectionWindow.hpp"

#include <opencv2/highgui/highgui.hpp>

ProjectionWindow::ProjectionWindow(cv::Point2i position, Calibration* calibration) : OpenCVWindow("Projection", position) {
	this->calibration = calibration;
}

void ProjectionWindow::processCameraFrame(cv::Mat frame_camera) {
	this->calibration->createFrameProjectionFromFrameCamera(this->frame, frame_camera);
}

cv::Mat ProjectionWindow::getFrame() const {
	return this->frame.clone();
}

void ProjectionWindow::draw() const {
	cv::imshow(this->name_window, this->frame);
}

