#include <opencv2/opencv.hpp>

#include "OpenCVUtil.hpp"


void OpenCVUtil::drawCrossOnImage(cv::Mat& image, const cv::Point2f& point, const cv::Scalar& color, const unsigned int size, const unsigned int thickness) {
	const int hsize = size / 2;
	cv::line(
		image,
		cv::Point(point.x - hsize, point.y),
		cv::Point(point.x + hsize, point.y),
		color,
		thickness	
	);
	cv::line(
		image,
		cv::Point(point.x, point.y - hsize),
		cv::Point(point.x, point.y + hsize),
		color,
		thickness	
	);
}
