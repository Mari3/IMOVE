#include <opencv2/opencv.hpp>

#include "../OpenCVUtil.hpp"
#include "Frame.hpp"

FrameWindow::FrameWindow(cv::Point2i position) : OpenCVWindow("Frame", position) { }

void FrameWindow::drawImage(cv::Mat& image_frame) {
	OpenCVWindow::drawImage(image_frame);
}

