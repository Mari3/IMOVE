#include <opencv2/core/core.hpp>

#include "../OpenCVWindow.hpp"
#include "../OpenCVUtil.hpp"
#include "../../../imove/src/calibration/Calibration.hpp"

class CalibrationMeterWindow : public OpenCVWindow {
	public:
		// UI calibration cross parameters
		const cv::Scalar COLOR_B_METER = OpenCVUtil::Color::GREEN;
		const cv::Scalar COLOR_A_METER = OpenCVUtil::Color::ORANGE;
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
		static void onMouse(int event, int x, int y, int flags, void* param);
		void onMouse(int event, int x, int y, int flags);

	protected:
		Calibration* calibration;
		bool entered_mouse = false;
		enum METER { A, B };
		
		// UI calibration meter parameters
		METER current_meter = METER::A;

		cv::Point2f coordinate_mouse;
		cv::Point2f a_meter, b_meter;

};
