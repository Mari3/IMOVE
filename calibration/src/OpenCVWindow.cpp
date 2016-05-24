#include "./OpenCVWindow.hpp"

#include <opencv2/highgui/highgui.hpp>

OpenCVWindow::OpenCVWindow(const char* name_window, cv::Point2i position) {
	this->name_window = name_window;
	cv::namedWindow(this->name_window, cv::WINDOW_NORMAL);
	cv::moveWindow(this->name_window, position.x, position.y);
}
