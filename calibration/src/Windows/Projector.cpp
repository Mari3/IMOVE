#include "./Projector.hpp"

ProjectorWindow::ProjectorWindow(cv::Point2i position) : OpenCVWindow("Projector", position) {
}

void ProjectorWindow::drawImage(cv::Mat& image_projector) {
	OpenCVWindow::drawImage(image_projector);
}

