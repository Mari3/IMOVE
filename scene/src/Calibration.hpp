#include <opencv2/imgproc/imgproc.hpp>

#include <vector>

class Calibration {
	public:
		Calibration(cv::Size& resolution_projector, cv::Mat& camera_projector_transformation);

		void createPointsProjectorFrameFromPointsCameraFrame(std::vector<cv::Point2f>& points_projector_frame, const std::vector<cv::Point2f>& points_camera_frame) const;
		void createProjectorCameraFrameFromCameraFrame(cv::Mat& projector_camera_frame, const cv::Mat& camera_frame) const;

	private:
		cv::Size resolution_projector;
		cv::Mat camera_projector_transformation;
};
