#include <opencv2/opencv.hpp>

#include "../../../util/src/OpenCVWindow.hpp"
#include "../../../util/src/Calibration.hpp"

class ProjectionWindow : public OpenCVWindow {
	public:
		ProjectionWindow(cv::Point2i position, cv::Size size, Calibration* calibration);
		
		void drawImage(cv::Mat image_camera);

	protected:
		Calibration* calibration;
};
