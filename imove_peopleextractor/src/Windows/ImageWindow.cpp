#include <opencv2/opencv.hpp>

#include "../../../imove_imp/src/OpenCVUtil.hpp"
#include "ImageWindow.hpp"

ImageWindow::ImageWindow(const char* name_window, cv::Point2i position) : OpenCVWindow(name_window, position) { }

void ImageWindow::drawImage(cv::Mat& image) {
	OpenCVWindow::drawImage(image);
}

