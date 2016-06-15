#include <opencv2/opencv.hpp>

#include "../../../imove_imp/src/OpenCVWindow.hpp"

// Window to display projector frame sequence to calibrate corners and frame delay
class ProjectorWindow : public OpenCVWindow {
	public:
		const unsigned int lanes = 24;
		
		ProjectorWindow(cv::Point2i position, cv::Size size);
		
		void drawImage(cv::Mat& image_projector);
	
	protected:
		unsigned int frame_offset = 0;
};
