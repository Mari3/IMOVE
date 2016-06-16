#include <opencv2/opencv.hpp>

#include "../ImageProcessing/PeopleExtractor.h"
#include "../../../util/src/OpenCVWindow.hpp"

// Window to display people extractor debug frame
class PeopleextractorWindow : public OpenCVWindow {
	public:
		PeopleextractorWindow(cv::Point2i position, cv::Size size, PeopleExtractor* peopleextractor);
		
		// Draw people extractor debug frame
		void drawFrame();

	protected:
		PeopleExtractor* peopleextractor;
};
