#include <opencv2/opencv.hpp>

#include "./../OpenCVWindow.hpp"

class ProjectorWindow : public OpenCVWindow {
	public:
		ProjectorWindow(cv::Point2i position);
		
		void drawImage(cv::Mat& image_projector);
	
		const unsigned int lanes = 24;
	protected:
		unsigned int frame_offset = 0;
};
