#include <opencv2/core/core.hpp>

#include "../OpenCVWindow.hpp"
#include "../../../imove/src/calibration/Calibration.hpp"

class CalibrationProjectionWindow : public OpenCVWindow {
	public:
		CalibrationProjectionWindow(cv::Point2i position, Calibration* calibration, cv::Size resolution_projector);
		
		void drawImage(cv::Mat image);

		// UI calibration cross parameters
		const int SIZE_CROSS = 10;
		const int THICKNESS_CROSS = 1;
		const int THICKNESS_LINE = 1;

		static const unsigned char REQUIRED_CORNERS = 4;
	//protected:

		Calibration* calibration;
		bool entered_mouse_projection = false;
		cv::Point2f coordinate_mouse_projection;
		unsigned int current_corner = 0;
		cv::Point2f* coordinate_corners_camera = new cv::Point2f[REQUIRED_CORNERS];
		cv::Point2f* coordinate_corners_projector = new cv::Point2f[REQUIRED_CORNERS];
		cv::Scalar* color_corners = new cv::Scalar[REQUIRED_CORNERS];

		static void onMouse(int event, int x, int y, int flags, void* userdata);
};
