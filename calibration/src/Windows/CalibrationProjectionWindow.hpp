#include <opencv2/core/core.hpp>

#include "../../../util/src/OpenCVWindow.hpp"
#include "../../../util/src/configuration/CameraConfiguration.hpp"
#include "../../../util/src/Projection.hpp"

// window to calibrate the projection coordinates on the camera and provide the transformation matrix to the projector coordinates
class CalibrationProjectionWindow : public OpenCVWindow {
	public:
		enum CORNER {
			TOPLEFT,
			TOPRIGHT,
			BOTTOMRIGHT,
			BOTTOMLEFT
		};
		// UI Calibration cross parameters
		const int SIZE_CROSS = 10;
		const int THICKNESS_CROSS = 1;
		const int THICKNESS_LINE = 1;

		// ui color of corners
		const cv::Scalar color_topleft;
		const cv::Scalar color_topright;
		const cv::Scalar color_bottomleft;
		const cv::Scalar color_bottomright;

		CalibrationProjectionWindow(cv::Point2i position, cv::Size size, ImoveConfiguration* calibration);
		
		void drawImage(cv::Mat image);
		
	protected:
		// coordinates of corners
		cv::Point2f coordinate_topleft;
		cv::Point2f coordinate_topright;
		cv::Point2f coordinate_bottomleft;
		cv::Point2f coordinate_bottomright;

		// current corner which will be set and draw setting my mouse coordinate cross
		CORNER current_corner = TOPLEFT;
		
		ImoveConfiguration* calibration;
		
		// position of mouse if ever moved over window
		bool entered_mouse_projection = false;
		cv::Point2f coordinate_mouse_projection;
		
		static void onMouse(int event, int x, int y, int flags, void* userdata);
		void onMouse(int event, int x, int y, int flags);
};
