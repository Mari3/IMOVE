#include "./Projection.hpp"

ProjectionWindow::ProjectionWindow(cv::Point2i position, Calibration* calibration) : OpenCVWindow("Projection", position) {
	this->calibration = calibration;
}

void ProjectionWindow::drawImage(cv::Mat image_camera) {
	cv::Mat image_projection;
	this->calibration->createFrameProjectionFromFrameCamera(image_projection, image_camera);
	OpenCVWindow::drawImage(image_projection);
}

