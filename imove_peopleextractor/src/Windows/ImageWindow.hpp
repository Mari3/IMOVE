#include <opencv2/opencv.hpp>

#include "../../../util/src/OpenCVWindow.hpp"

// Window to display camera frame for debugging information 
class ImageWindow : public OpenCVWindow {
	public:
		ImageWindow(const char* name_window, cv::Point2i position, cv::Size size);
		
		// draw image 
		void drawImage(cv::Mat& image);
};
