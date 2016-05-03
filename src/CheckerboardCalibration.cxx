// Found at http://programmingexamples.net/wiki/OpenCV/CheckerboardCalibration
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
 
#include <iostream>
#include <string>
 
std::vector<cv::Point2f> createChessboardCorners(cv::Size checkerboard_size, float squareSize);

// @source http://stackoverflow.com/questions/217578/how-can-i-determine-whether-a-2d-point-is-within-a-polygon/2922778#2922778
//bool pointInPolygon(std::vector<cv::Point2f> vertices, cv::Point2f test_point) {
//	int i, j,
//	bool c = false;
//	for (i = 0, j = vertices.size() - 1; i < vertices.size(); j = i++) {
//		if ( (
//			(vertices[1][i] > test_point[1]) != (vertices[j][1] > test_point[1])
//		) && (
//			test_point[0] < (vertices[j][0] - vertices[i][0])
//			* (test_point[1] - vertices[i][1])
//			/ (
//				vertices[j][1] - vertices[i][1]
//			) + vertices[i][0]
//		) ) {
//			c = !c;
//	}
//	return c;
//}
//
//cv::Point2f calcProjectorPointFromCameraPoint(cv::Point2F point_on_camera, cv::Size project_resolution, cv::Size checkerboard_size, std::vector<cv::Point2f> camera_objectPoints) {
//	cv::Point2f projector_location;
//
//	std::vector<cv::Point2f> projector_objectPoints(camera_objectPoints.size());
//	for (int cy = 0; cy < checkerboard_size.heigh; cy++) {
//		for (int cx = 0; cx < checkerboard_size.width; cx++) {
//			projector_objectPoints.push_back(cv::Point2f(
//				project_resolution.width * (cx + 1) / (checkerboard_size.width + 1),
//				project_resolution.height * (cy + 1) / (checkerboard_size.height + 1)
//			));
//		}
//	}
//	cv::Mat camera_projector_transformation = cv::estimateRigidTransform(camera_objectPoints, projector_objectPoints, true);
//
//
//	std::vector<cv::Point2f> vertices(4);
//	int index_topleftx, index_toplefty;
//
//	cv::Point3f objectPoint;
//	for (int cy = 0; cy < checkerboard_size.height - 1; cy++) {
//		for (int cx = 0; cx < checkerboard_size.width - 1; cx++) {
//			vertices.push_back(objectPoints[cy * checkerboard_size.width + cx]);
//			vertices.push_back(objectPoints[cy * checkerboard_size.width + cx + 1]);
//			vertices.push_back(objectPoints[(cy + 1) * checkerboard_size.width + cx]);
//			vertices.push_back(objectPoints[(cy + 1) * checkerboard_size.width + cx + 1]);
//			if (pointInPolygon(vertices, point_on_camera)) {
//				objectPoint = cv::Point3f(
//					vertices[0]
//				);
//			}
//			vertices.empty();
//		}
//	}
//
//	return projector_location;
//}
 
int main(int argc, char* argv[]) {
	// Specify the number of squares along each dimension of the board.
	// This is actually the number of "inside corners" (where a black square meets a white square).
	// That is, if the board is composed of n x m squares, you would use (n-1, m-1) as the arguments.
	// For example, for a standard checkerboard (8x8 squares), you would use:
	cv::Size checkerboard_size(9, 6);
 
	cv::Mat image = cv::imread(argv[1], 1);
	cv::Mat pattern = cv::imread(argv[2], 1);
	if (image.empty()) {
		std::cerr << "Image not read correctly!" << std::endl;
		exit(-1);
	}
	if (pattern.empty()) {
		std::cerr << "Pattern not read correctly!" << std::endl;
		exit(-1);
	}
	//cv::Size project_resolution(1665, 1166);
	//cv::Size project_resolution(480, 336);
	cv::Size project_resolution(pattern.size().width, pattern.size().height);
	float squareSize = (project_resolution.width / (checkerboard_size.width + 1) + project_resolution.height / (checkerboard_size.height + 1)) / 2; // This is "1 arbitrary unit"
 
	cv::namedWindow("Image View", 1);
	cv::namedWindow("Undistorted Image View", 1);
	cv::namedWindow("Pattern View", 1);
 
	std::vector<cv::Point2f> objectPoints = createChessboardCorners(
		checkerboard_size,
		squareSize
	);
	
	// Find the chessboard corners
	std::vector<cv::Point2f> imagePoints;
	bool found = cv::findChessboardCorners(
		image,
		checkerboard_size,
		imagePoints
	);
	if (!found) {
		std::cerr << "Could not find chess board!" << std::endl;
		exit(-1);
	}

	std::vector<std::vector<cv::Point2f> > image2DPoints(1);
	image2DPoints[0] = imagePoints;

	std::vector<cv::Point3f> p3Dpoints(objectPoints.size());
	for (int i = 0; i < objectPoints.size(); i++) {
		p3Dpoints[i] = cv::Point3f(
			objectPoints[i].x,
			objectPoints[i].y,
			0
		);
	}
	std::vector<std::vector<cv::Point3f> > object3DPoints(1);
	object3DPoints[0] = p3Dpoints;
 
	cv::Mat distortionCoefficients = cv::Mat::zeros(8, 1, CV_64F); // There are 8 distortion coefficients
	cv::Mat cameraMatrix = cv::Mat::eye(3, 3, CV_64F);

	std::vector<cv::Mat> rotationVectors;
	std::vector<cv::Mat> translationVectors;
	int flags = 0;
std::cout << "BEFORE" << std::endl;
	double rms = cv::calibrateCamera(
		object3DPoints,
		image2DPoints,
		image.size(),
		cameraMatrix,
		distortionCoefficients,
		rotationVectors,
		translationVectors,
		0 //flags|CV_CALIB_FIX_K4|CV_CALIB_FIX_K5
	);
std::cout << "AFTER" << std::endl;
 
	std::cout << "RMS: " << rms << std::endl;
	std::cout << "Checkers object points: " << objectPoints << std::endl;
	std::cout << "Checkers image points: " << imagePoints << std::endl; //TODO map 256x248 to a point in the 9 x 6
	std::cout << "Camera matrix: " << cameraMatrix << std::endl;
	std::cout << "Distortion _coefficients: " << distortionCoefficients << std::endl;
	
	cv::Mat undistorted;
	cv::undistort(image, undistorted, cameraMatrix, distortionCoefficients);
	
	std::vector<cv::Point2f> undistortedImagePoints;
	cv::undistortPoints(imagePoints, undistortedImagePoints, cameraMatrix, distortionCoefficients);
	std::cout << "Undistorted Checkers points: " << undistortedImagePoints << std::endl;
	
	cv::drawChessboardCorners(image, checkerboard_size, cv::Mat(imagePoints), found);
	cv::drawChessboardCorners(undistorted, checkerboard_size, cv::Mat(imagePoints), found);
	cv::drawChessboardCorners(undistorted, checkerboard_size, cv::Mat(undistortedImagePoints), found);
	cv::drawChessboardCorners(pattern, checkerboard_size, cv::Mat(imagePoints), found);
	cv::drawChessboardCorners(pattern, checkerboard_size, cv::Mat(undistortedImagePoints), found);
	cv::drawChessboardCorners(pattern, checkerboard_size, cv::Mat(objectPoints), found);
	 
	cv::imshow("Image View", image);
	cv::imshow("Undistorted Image View", undistorted);
	cv::imshow("Pattern View", pattern);
	cv::moveWindow("Undistorted Image View", image.size().width, 0);
	cv::moveWindow("Pattern View", image.size().width * 2, 0);
	cv::waitKey(0);
 
	return 0;
}
 
std::vector<cv::Point2f> createChessboardCorners(const cv::Size checkerboard_size, const float squareSize) {
	std::vector<cv::Point2f> corners;
 
	for (int y = 0; y < checkerboard_size.height; y++) {
		for (int x = 0; x < checkerboard_size.width; x++) {
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
