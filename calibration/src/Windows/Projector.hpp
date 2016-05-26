#include <opencv2/opencv.hpp>

#include "./../OpenCVWindow.hpp"

class ProjectorWindow : public OpenCVWindow {
	public:
		const unsigned int lanes = 24;
		
		ProjectorWindow(cv::Point2i position);
		
		void drawImage(cv::Mat& image_projector);
	
	protected:
		unsigned int frame_offset = 0;
};
