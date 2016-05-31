#include <opencv2/opencv.hpp>

#include "../../../imove-peopleextractor/src/OpenCVWindow.hpp"
#include "../../../imove-peopleextractor/src/Calibration/Calibration.hpp"

// Window to calibrate the elimination of the projection on the camera based on the projector frame with some delay and intensity
class EliminateProjectionWindow : public OpenCVWindow {
	public:
		const char* name_trackbar_ratio_projector_background_light = "Ratio projector - background light";
		const char* name_trackbar_frames_projector_camera_delay = "Frames projector - camera delay";
		
		void drawImage(cv::Mat image_camera);

		EliminateProjectionWindow(cv::Point2i position, Calibration* calibration);

	protected:
		Calibration* calibration;
	
		int track_projector_background_light;
		int track_frames_projector_camera_delay;

		const int INT_FULL_PERCENTAGE = 100;
		const double DOUBLE_FULL_PERCENTAGE = 100.0;
		
		static void onProjectorBackgroundLight(int tracked_int, void *param);
		static void onFramesProjectorCameraDelay(int tracked_int, void *param);
};
