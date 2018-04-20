#include "OpenCVWindow.hpp"

#include <opencv2/highgui/highgui.hpp>

OpenCVWindow::OpenCVWindow(const char* name_window, cv::Point2i position, cv::Size size) {
	this->name_window = name_window;
	cv::namedWindow(this->name_window, 1);
	cv::moveWindow(this->name_window, position.x, position.y);
	//cv::resizeWindow(this->name_window, size.width, size.height);
}

cv::Mat OpenCVWindow::getClonedImage() const {
	return this->image.clone();
}

void OpenCVWindow::drawImage(cv::Mat& image) {
	this->image = image;
	cv::imshow(this->name_window, this->image);
}
