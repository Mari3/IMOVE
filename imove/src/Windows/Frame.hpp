#include <opencv2/opencv.hpp>

#include "../OpenCVWindow.hpp"

// Window to display projector frame sequence to calibrate corners and frame delay
class FrameWindow : public OpenCVWindow {
	public:
		FrameWindow(cv::Point2i position);
		
		void drawImage(cv::Mat& image_frame);
};
