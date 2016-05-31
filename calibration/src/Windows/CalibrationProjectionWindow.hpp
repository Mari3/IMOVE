#include <opencv2/core/core.hpp>

#include "../../../imove_peopleextractor/src/OpenCVWindow.hpp"
#include "../../../imove_peopleextractor/src/Calibration/Calibration.hpp"

// window to calibrate the projection coordinates on the camera and provide the transformation matrix to the projector coordinates
class CalibrationProjectionWindow : public OpenCVWindow {
	public:
		// UI Calibration cross parameters
		const int SIZE_CROSS = 10;
		const int THICKNESS_CROSS = 1;
		const int THICKNESS_LINE = 1;
		
		CalibrationProjectionWindow(cv::Point2i position, Calibration* calibration);
		
		void drawImage(cv::Mat image);
		
	protected:
		static const unsigned char REQUIRED_CORNERS = 4;
		
		Calibration* calibration;
		
		// position of mouse if ever moved over window
		bool entered_mouse_projection = false;
		cv::Point2f coordinate_mouse_projection;
		
		// current corner which will be set and draw setting my mouse coordinate cross
		unsigned int current_corner = 0;
		
		// perspective corners selected on camera
		cv::Point2f* coordinate_corners_camera = new cv::Point2f[REQUIRED_CORNERS];
		// colours of crosses of corners of perspective square
		cv::Scalar* color_corners = new cv::Scalar[REQUIRED_CORNERS];
		// corners of projector
		cv::Point2f* coordinate_corners_projector = new cv::Point2f[REQUIRED_CORNERS];
		
		static void onMouse(int event, int x, int y, int flags, void* userdata);
		void onMouse(int event, int x, int y, int flags);
		
};
