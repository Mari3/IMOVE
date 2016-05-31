#include <opencv2/opencv.hpp>

#include "../OpenCVWindow.hpp"

// Window to display people extractor debug frame
class FrameWindow : public OpenCVWindow {
	public:
		FrameWindow(cv::Point2i position);
		
		// Draw people extractor debug frame
		void drawImage(cv::Mat& image_frame);
};
