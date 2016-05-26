#include "./OpenCVWindow.hpp"

#include <opencv2/highgui/highgui.hpp>

OpenCVWindow::OpenCVWindow(const char* name_window, cv::Point2i position) {
	this->name_window = name_window;
	cv::namedWindow(this->name_window, cv::WINDOW_NORMAL);
	cv::moveWindow(this->name_window, position.x, position.y);
}

cv::Mat OpenCVWindow::getClonedImage() const {
	return this->image.clone();
}

void OpenCVWindow::drawImage(cv::Mat& image) {
	this->image = image;
	cv::imshow(this->name_window, this->image);
}
