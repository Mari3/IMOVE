#include <opencv2/opencv.hpp>

#include "../../../util/src/OpenCVUtil.hpp"
#include "PeopleextractorWindow.hpp"

PeopleextractorWindow::PeopleextractorWindow(cv::Point2i position, cv::Size size, PeopleExtractor* peopleextractor) : OpenCVWindow("Frame", position, size), peopleextractor(peopleextractor) { }

void PeopleextractorWindow::drawFrame() {
	cv::Mat debug_frame = peopleextractor->getDebugFrame();
	OpenCVWindow::drawImage(debug_frame);
}

