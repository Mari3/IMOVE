#include <opencv2/opencv.hpp>

#include "../../../util/src/OpenCVWindow.hpp"
#include "../../../util/src/Calibration.hpp"
#include "../../../util/src/Projection.hpp"

// Window to calibrate the elimination of the projection on the camera based on the projector frame with some delay and intensity
class EliminateProjectionWindow : public OpenCVWindow {
	public:
		const char* name_trackbar_ratio_projector_background_light = "Ratio projector - background light";
		const char* name_trackbar_frames_projector_camera_delay = "Frames projector - camera delay";
		
		void drawImage(cv::Mat image_camera);

		EliminateProjectionWindow(cv::Point2i position, cv::Size size, Calibration* calibration, Projection* projection);

	protected:
		Calibration* calibration;
		Projection* projection;
	
		int track_projector_background_light;
		int track_frames_projector_camera_delay;

		const int INT_FULL_PERCENTAGE = 100;
		const float FLOAT_FULL_PERCENTAGE = 100.0f;
		
		static void onProjectorBackgroundLight(int tracked_int, void *param);
		static void onFramesProjectorCameraDelay(int tracked_int, void *param);
};
