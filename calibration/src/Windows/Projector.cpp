#include <opencv2/opencv.hpp>

#include "../OpenCVUtil.hpp"
#include "./Projector.hpp"

ProjectorWindow::ProjectorWindow(cv::Point2i position) : OpenCVWindow("Projector", position) {
	
}

void ProjectorWindow::drawImage(cv::Mat& image_projector) {
	cv::Size resolution_projector = image_projector.size();
	const cv::Size size_lane(resolution_projector.width / this->lanes, resolution_projector.height / this->lanes);
	for (unsigned int x = 0; x < (unsigned int) resolution_projector.width; ++x) {
		for (unsigned int y = 0; y < (unsigned int) resolution_projector.height; ++y) {
			image_projector.at<cv::Vec3b>(y, x) = cv::Vec3b(
				0,
				(unsigned char) ((OpenCVUtil::U8_FULL * ((x + this->frame_offset * size_lane.width) / size_lane.width)) / size_lane.width),
				(unsigned char) ((OpenCVUtil::U8_FULL * ((resolution_projector.height - (y + this->frame_offset * size_lane.height)) / size_lane.height)) / size_lane.height)
			);
		}
	}
	this->frame_offset = (this->frame_offset + 1) % this->lanes;
	OpenCVWindow::drawImage(image_projector);
}

