#include <opencv2/opencv.hpp>

#include "../../../imove_imp/src/OpenCVWindow.hpp"

// Window to display camera frame for debugging information 
class ImageWindow : public OpenCVWindow {
	public:
		ImageWindow(const char* name_window, cv::Point2i position);
		
		// draw image 
		void drawImage(cv::Mat& image);
};
