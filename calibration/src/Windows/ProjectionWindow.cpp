#include "ProjectionWindow.hpp"

ProjectionWindow::ProjectionWindow(cv::Point2i position, cv::Size size, Projection& projection) : OpenCVWindow("Projection", position, size), projection(projection) {}

void ProjectionWindow::drawImage(cv::Mat image_camera) {
	cv::Mat image_projection;
	this->projection.createFrameProjectionFromFrameCamera(image_projection, image_camera);
	OpenCVWindow::drawImage(image_projection);
}

