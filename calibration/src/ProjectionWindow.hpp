#include "./OpenCVWindow.hpp"
#include "../../imove/src/calibration/Calibration.hpp"

class ProjectionWindow : public OpenCVWindow {
	public:
		ProjectionWindow(cv::Point2i position, Calibration* calibration);
		
		void processCameraFrame(cv::Mat frame_camera);

		cv::Mat getFrame() const;
		
		void draw() const;

	protected:
		Calibration* calibration;
		cv::Mat frame;

	private:
		const char* name_window = "Projection";
};
