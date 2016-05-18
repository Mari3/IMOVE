#include <opencv2/imgproc/imgproc.hpp>

#include <vector>
#include <queue>

class Calibration {
	public:
		Calibration(const cv::Size& resolution_projector, cv::Mat& camera_projector_transformation, unsigned int frames_projector_camera_delay, double projector_background_light);

		void feedFrameProjector(const cv::Mat& frame_projector);
		void eliminateProjectionFeedbackFromFrameCamera(cv::Mat& frame_projectioneliminated, const cv::Mat& frame_camera);
		void createPointsFrameProjectorFromPointsFrameCamera(std::vector<cv::Point2f>& points_frame_projector, const std::vector<cv::Point2f>& points_frame_camera) const;
		void createFrameProjectionFromFrameCamera(cv::Mat& frame_projection, const cv::Mat& frame_camera) const;

		void setFramesProjectorCameraDelay(unsigned int frames_projector_camera_delay);
		void setProjectorBackgroundLight(double projector_background_light);
		void setCameraProjectorTransformation(cv::Mat& camera_projector_transformation);

	private:
		cv::Size resolution_projector;
		cv::Mat camera_projector_transformation;
		std::queue<cv::Mat> frames_delay_projector;
		unsigned int frames_projector_camera_delay;
		double projector_background_light;
};
