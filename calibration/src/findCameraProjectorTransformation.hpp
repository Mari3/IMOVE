#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"

#include <vector>

std::vector<cv::Point2f> createChessboardCorners(const cv::Size size_checkerboard, const cv::Size resolution);
cv::Point2f* getCornersFromCheckerboard(const std::vector<cv::Point2f> checkerboard_points, const cv::Size size_checkerboard);
cv::Mat findCameraProjectorTransformationFromCheckerboard(const cv::Mat camera_frame, const cv::Size resolution_projector, const cv::Size size_checkerboard);
