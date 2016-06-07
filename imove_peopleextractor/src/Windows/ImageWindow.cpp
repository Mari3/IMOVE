#include <opencv2/opencv.hpp>

#include "../OpenCVUtil.hpp"
#include "ImageWindow.hpp"

ImageWindow::ImageWindow(const char* name_window, cv::Point2i position) : OpenCVWindow(name_window, position) { }

void ImageWindow::drawImage(cv::Mat& image) {
	OpenCVWindow::drawImage(image);
}

