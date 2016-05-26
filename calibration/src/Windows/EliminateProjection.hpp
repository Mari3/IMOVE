#include <opencv2/opencv.hpp>

#include "./../OpenCVWindow.hpp"
#include "../../../imove/src/calibration/Calibration.hpp"

class EliminateProjectionWindow : public OpenCVWindow {
	public:
		EliminateProjectionWindow(cv::Point2i position, Calibration* calibration, double projector_background_light, unsigned int frames_projector_camera_delay);
		
		void drawImage(cv::Mat image_camera);

		static void onProjectorBackgroundLight(int tracked_int, void *param);
		static void onFramesProjectorCameraDelay(int tracked_int, void *param);

		const int INT_FULL_PERCENTAGE = 100;
		const double DOUBLE_FULL_PERCENTAGE = 100.0;
	
		int track_projector_background_light;
		int track_frames_projector_camera_delay;
		const char* name_trackbar_ratio_projector_background_light = "Ratio projector - background light";
		const char* name_trackbar_frames_projector_camera_delay = "Frames projector - camera delay";

	protected:
		Calibration* calibration;
};
