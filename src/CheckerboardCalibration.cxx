#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
 
#include <iostream>
#include <string>
 
std::vector<cv::Point2f> createChessboardCorners(const cv::Size size_checkerboard, const cv::Size resolution);
cv::Point2f* getCornersFromCheckerboard(const std::vector<cv::Point2f> checkerboard_points, const cv::Size size_checkerboard);
cv::Mat findCameraProjectorTransformationFromCheckerboard(const cv::Mat camera_frame, const cv::Mat projector_frame, const cv::Size size_checkerboard);

int main(int argc, char* argv[]) {
	const cv::Size size_checkerboard(9, 6); //todo config

	if (argc != 3) {
		std::cout << "Usage: <path to camera frame (image)> <path to projector frame (image)>";
		return 0;
	}
 
	cv::Mat camera_frame = cv::imread(argv[1], 1);
	cv::Mat projector_frame = cv::imread(argv[2], 1);
	if (camera_frame.empty()) {
		std::cerr << "Camera frame not read correctly!" << std::endl;
		return -1;
	}
	if (projector_frame.empty()) {
		std::cerr << "Projector frame not read correctly!" << std::endl;
		return -1;
	}

	const cv::Mat camera_projector_transformation = findCameraProjectorTransformationFromCheckerboard(camera_frame, projector_frame, size_checkerboard);

	cv::Mat derived_projector_frame;
	cv::warpPerspective(
		camera_frame,
		derived_projector_frame,
		camera_projector_transformation,
		projector_frame.size()
	);
	
	std::vector<cv::Point2f> points_camera_frame(1);
	points_camera_frame[0] = cv::Point2f(
		std::rand() * camera_frame.size().width,
		std::rand() * camera_frame.size().height
	);
	std::vector<cv::Point2f> points_projector_frame;
	perspectiveTransform(
		points_camera_frame,
		points_projector_frame,
		camera_projector_transformation
	);
	
	cv::namedWindow("Camera view", 1);
	cv::namedWindow("Derived projector view", 1);
	cv::moveWindow("Undistorted Image View", camera_frame.size().width, 0);
	cv::namedWindow("Projector view", 1);
	cv::moveWindow("Undistorted Image View", camera_frame.size().width + derived_projector_frame.size().width, 0);
	cv::imshow("Camera view", camera_frame);
	cv::imshow("Derived projector view", derived_projector_frame);
	cv::imshow("Projector view", derived_projector_frame);

	cv::waitKey(0);
 
	return 0;
}

cv::Mat findCameraProjectorTransformationFromCheckerboard(const cv::Mat camera_frame, const cv::Mat projector_frame, const cv::Size size_checkerboard) {
	if (camera_frame.empty()) {
		std::cerr << "Image not read correctly!" << std::endl;
		exit(-1);
	}
	if (projector_frame.empty()) {
		std::cerr << "Pattern not read correctly!" << std::endl;
		exit(-1);
	}
 
	std::vector<cv::Point2f> checkerboard_points_projector_frame = createChessboardCorners(
		size_checkerboard,
		projector_frame.size()
	);
	
	std::vector<cv::Point2f> checkerboard_points_camera_frame;
	bool found = cv::findChessboardCorners(
		camera_frame,
		size_checkerboard,
		checkerboard_points_camera_frame
	);
	if (!found) {
		std::cerr << "Could not find chess board!" << std::endl;
		exit(-1);
	}

	std::vector<std::vector<cv::Point2f> > image2DPoints(1);
	image2DPoints[0] = checkerboard_points_camera_frame;

	std::vector<cv::Point3f> p3Dpoints(checkerboard_points_camera_frame.size());
	for (unsigned int i = 0; i < checkerboard_points_projector_frame.size(); i++) {
		p3Dpoints[i] = cv::Point3f(
			checkerboard_points_projector_frame[i].x,
			checkerboard_points_projector_frame[i].y,
			0
		);
	}
	std::vector<std::vector<cv::Point3f> > object3DPoints(1);
	object3DPoints[0] = p3Dpoints;
	
	return cv::getPerspectiveTransform(
		getCornersFromCheckerboard(
			checkerboard_points_camera_frame,
			size_checkerboard
		),
		getCornersFromCheckerboard(
			checkerboard_points_projector_frame,
			size_checkerboard
		)
	);
}
 
std::vector<cv::Point2f> createChessboardCorners(const cv::Size size_checkerboard, const cv::Size resolution) {
	std::vector<cv::Point2f> corners;
	const float squareSize = (resolution.width / (size_checkerboard.width + 1) + resolution.height / (size_checkerboard.height + 1)) / 2;
 
	for (int y = 0; y < size_checkerboard.height; y++) {
		for (int x = 0; x < size_checkerboard.width; x++) {
			corners.push_back(
				cv::Point2f(
					float(x + 1) * squareSize,
					float(y + 1) * squareSize
				)
			);
		}
	}
 
	return corners;
}

cv::Point2f* getCornersFromCheckerboard(const std::vector<cv::Point2f> checkerboard_points, const cv::Size size_checkerboard) {
	cv::Point2f* corners = new cv::Point2f[4];
	corners[0] = checkerboard_points[0]; // top left
	corners[1] = checkerboard_points[size_checkerboard.width - 1]; // top right
	corners[2] = checkerboard_points[(size_checkerboard.height - 1) * size_checkerboard.width]; // bottom left
	corners[3] = checkerboard_points[size_checkerboard.height * size_checkerboard.width - 1]; // bottom right
	return corners;
}
