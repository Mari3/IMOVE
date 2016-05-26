#include <opencv2/core/core.hpp>

#include "../OpenCVWindow.hpp"
#include "../OpenCVUtil.hpp"
#include "../../../imove/src/calibration/Calibration.hpp"

class CalibrationMeterWindow : public OpenCVWindow {
	public:
		CalibrationMeterWindow(cv::Point2i position, Calibration* calibration, float meter);
		
		void drawImage(cv::Mat image);

		// UI calibration cross parameters
		const int SIZE_CROSS = 10;
		const int THICKNESS_CROSS = 1;
		const int THICKNESS_LINE = 1;

		float getMeter() const;
	//protected:

		Calibration* calibration;
		bool entered_mouse = false;
		enum METER { A, B };
		
		// UI calibration meter parameters
		const cv::Scalar COLOR_A_METER = OpenCVUtil::Color::ORANGE;
		const cv::Scalar COLOR_B_METER = OpenCVUtil::Color::GREEN;
		METER current_meter = METER::A;
		cv::Point2f coordinate_mouse;

		cv::Point2f a_meter, b_meter;

		static void onMouse(int event, int x, int y, int flags, void* userdata);
};
