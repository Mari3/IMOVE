#include <opencv2/opencv.hpp>

#include "../../../imove_imp/src/OpenCVWindow.hpp"
#include "../../../scene_interface/src/People.h"

// Window to display camera frame for debugging information 
class DetectedPeopleCameraWindow : public OpenCVWindow {
	public:
		// ui debug elements
		const unsigned int SIZE_CIRCLE_CAMERA_DEBUG = 20;
		const unsigned int THICKNESS_CIRCLE_CAMERA_DEBUG = 2;
		
		DetectedPeopleCameraWindow(cv::Point2i position, cv::Size size);
		
		// draw detected people in the camera frame
		void drawImage(cv::Mat& image_camera, scene_interface::People& detectedpeople);
};
