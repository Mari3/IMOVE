#include <opencv2/opencv.hpp>

#include "../../../imove_imp/src/OpenCVUtil.hpp"
#include "PeopleextractorWindow.hpp"

PeopleextractorWindow::PeopleextractorWindow(cv::Point2i position, PeopleExtractor* peopleextractor) : OpenCVWindow("Frame", position), peopleextractor(peopleextractor) { }

void PeopleextractorWindow::drawFrame() {
	cv::Mat debug_frame = peopleextractor->getDebugFrame();
	OpenCVWindow::drawImage(debug_frame);
}

