#include <opencv2/core/core.hpp>

#include "../OpenCVWindow.hpp"
#include "../OpenCVUtil.hpp"
#include "../../../imove/src/calibration/Calibration.hpp"

class CalibrationMeterWindow : public OpenCVWindow {
	public:
		// UI calibration cross parameters
		const cv::Scalar COLOR_A_METER = OpenCVUtil::Color::ORANGE;
		const cv::Scalar COLOR_B_METER = OpenCVUtil::Color::GREEN;
		const int SIZE_CROSS = 10;
		const int THICKNESS_CROSS = 1;
		const int THICKNESS_LINE = 1;
		
		CalibrationMeterWindow(cv::Point2i position, Calibration* calibration, float meter);
		
		/**
		 * Draws meter and last mouse position on image using line and crosses
		 * 
		 * @param image Image to draw meter and last mouse position on
		 **/
		void drawImage(cv::Mat image);
		
		float getMeter() const;

	protected:
		enum METER { A, B };
		
		Calibration* calibration;
	
		// starting toggling which meter is getting selected
		METER current_meter = METER::A;
		// true iff mouse moved over window, to start drawing (last known) coordinate of mouse
		bool entered_mouse = false;
		// last known mouse coordinate
		cv::Point2f coordinate_mouse;
		
		// current meter point a and b
		cv::Point2f a_meter;
		
		// Calibrate projection mouse callback
		static void onMouse(int event, int x, int y, int flags, void* param);
		void onMouse(int event, int x, int y, int flags);
		
		cv::Point2f b_meter;
};
