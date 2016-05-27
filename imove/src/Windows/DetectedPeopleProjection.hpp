#include <opencv2/opencv.hpp>

#include "../OpenCVWindow.hpp"
#include "../interface/Person.h"

// Window to display projection frame for debugging information
class DetectedPeopleProjectionWindow : public OpenCVWindow {
	public:
		// ui debug elements
		const unsigned int SIZE_CIRCLE_PROJECTION_DEBUG = 80;
		const unsigned int THICKNESS_CIRCLE_PROJECTION_DEBUG = 8;
		const unsigned int SIZE_FONT_DEBUG = 1;
		
		DetectedPeopleProjectionWindow(cv::Point2i position);
		
		void drawImage(cv::Mat& image_projection, vector<Person>& detectedpeople_projection);
};
