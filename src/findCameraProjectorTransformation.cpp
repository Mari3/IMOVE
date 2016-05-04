#include "findCameraProjectorTransformation.hpp"
#include <iostream>

cv::Mat findCameraProjectorTransformationFromCheckerboard(const cv::Mat camera_frame, const cv::Size resolution_projector, const cv::Size size_checkerboard) {
	if (camera_frame.empty()) {
		std::cerr << "Image not read correctly!" << std::endl;
		exit(-1);
	}
 
	std::vector<cv::Point2f> checkerboard_points_projector_frame = createChessboardCorners(
		size_checkerboard,
		resolution_projector
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
