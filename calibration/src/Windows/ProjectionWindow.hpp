#include <opencv2/opencv.hpp>

#include "../../../imove-peopleextractor/src/OpenCVWindow.hpp"
#include "../../../imove-peopleextractor/src/Calibration/Calibration.hpp"

class ProjectionWindow : public OpenCVWindow {
	public:
		ProjectionWindow(cv::Point2i position, Calibration* calibration);
		
		void drawImage(cv::Mat image_camera);

	protected:
		Calibration* calibration;
};
