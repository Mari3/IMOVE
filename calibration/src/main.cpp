#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/persistence.hpp>
 
#include <iostream>
#include <string>

const unsigned char U8_WHITE = 255;
const signed int NOKEY_ANYKEY = -1;

const cv::Point2f ORIGIN2D = cv::Point2f(
	0,
	0
);

const unsigned char REQUIRED_CORNERS = 4;
cv::Point2f* coordinate_corners_camera = new cv::Point2f[REQUIRED_CORNERS];
cv::Scalar* scalar_corners = new cv::Scalar[REQUIRED_CORNERS];
unsigned int amount_corners = 0;

bool mouse_entered = false;
cv::Point2f coordinate_mouse;
cv::Scalar scalar_mouse = cv::Scalar(255, 0, 255);

const int CROSS_SIZE = 10;
const int CROSS_HSIZE = CROSS_SIZE / 2;
const int CROSS_THICKNESS = 2;

void drawCrossOnImage(cv::Mat& image, cv::Point2f& point, cv::Scalar& color) {
	cv::line(
		image,
		cv::Point(point.x - CROSS_HSIZE, point.y),
		cv::Point(point.x + CROSS_HSIZE, point.y),
		color,
		CROSS_THICKNESS
	);
	cv::line(
		image,
		cv::Point(point.x, point.y - CROSS_HSIZE),
		cv::Point(point.x, point.y + CROSS_HSIZE),
		color,
		CROSS_THICKNESS
	);
}

void drawCornersOnImage(cv::Mat& image) {
	for (unsigned int i = 0; i < amount_corners; ++i) {
		drawCrossOnImage(image, coordinate_corners_camera[i], scalar_corners[i]);
	}
	if (mouse_entered) {
		drawCrossOnImage(image, coordinate_mouse, scalar_mouse);
	}
}

void cameraWindowMouseEvent(int event, int x, int y, int flags, void* userdata) {
	coordinate_mouse = cv::Point2f(x, y);
	mouse_entered = true;

	if (flags & cv::EVENT_FLAG_LBUTTON && amount_corners < REQUIRED_CORNERS) {
		coordinate_corners_camera[amount_corners] = coordinate_mouse;
		++amount_corners;
	}
}

int main(int argc, char* argv[]) {
	scalar_corners[0] = cv::Scalar(255,  0,    0);
	scalar_corners[1] = cv::Scalar(0,   255,   0);
	scalar_corners[2] = cv::Scalar(0,     0, 255);
	scalar_corners[3] = cv::Scalar(255, 255,   0);
	
	if (argc != 5) {
		std::cout << "Usage: <path to configuration file> <int video device> <projector resolution width> <projector resolution height>" << std::endl;
		return EXIT_SUCCESS;
	}
 
	const cv::Size resolution_projector(std::stoi(argv[3]), std::stoi(argv[4]));
	
	cv::Mat projector_frame = cv::Mat::ones(resolution_projector.width, resolution_projector.height, CV_8UC3) * U8_WHITE;
	cv::namedWindow("Projector", cv::WINDOW_NORMAL | cv::WINDOW_AUTOSIZE);
	cv::moveWindow("Projector", 0, 0);
	cv::imshow("Projector", projector_frame);

	cv::Mat frame_camera;
	cv::VideoCapture video_capture(std::stoi(argv[2]));
	cv::namedWindow("Camera", cv::WINDOW_NORMAL | cv::WINDOW_AUTOSIZE);
	cv::moveWindow("Camera", 500, 0);
	cv::setMouseCallback("Camera", cameraWindowMouseEvent, NULL);
	
	while (amount_corners < REQUIRED_CORNERS) {
		if (!video_capture.read(frame_camera)) {
			std::cerr << "Unable to read next frame." << std::endl;
			std::cerr << "Exiting..." << std::endl;
			return EXIT_FAILURE;
		}
		drawCornersOnImage(frame_camera);
		cv::imshow("Camera", frame_camera);
		cv::waitKey(1);
	}
	cv::Point2f* coordinate_corners_projector = new cv::Point2f[REQUIRED_CORNERS];
	coordinate_corners_projector[0] = cv::Point2f(                    ORIGIN2D.x,                      ORIGIN2D.y);
	coordinate_corners_projector[1] = cv::Point2f(resolution_projector.width - 1,                      ORIGIN2D.y);
	coordinate_corners_projector[2] = cv::Point2f(										ORIGIN2D.x, resolution_projector.height - 1);
	coordinate_corners_projector[3] = cv::Point2f(resolution_projector.width - 1, resolution_projector.height - 1);
	const cv::Mat camera_projector_transformation = cv::getPerspectiveTransform(
		coordinate_corners_camera,
		coordinate_corners_projector
	);
	std::cout << camera_projector_transformation << std::endl;

	cv::namedWindow("Projection", cv::WINDOW_NORMAL | cv::WINDOW_AUTOSIZE);
	cv::moveWindow("Projection", 1000, 0);
	cv::Mat frame_projection;
	while (cv::waitKey(1) == NOKEY_ANYKEY) {
		if (!video_capture.read(frame_camera)) {
			std::cerr << "Unable to read next frame." << std::endl;
			std::cerr << "Exiting..." << std::endl;
			return EXIT_FAILURE;
		}
		drawCornersOnImage(frame_camera);
		cv::imshow("Camera", frame_camera);
		cv::warpPerspective(
			frame_camera,
			frame_projection,
			camera_projector_transformation,
			resolution_projector
		);
		cv::imshow("Projection", frame_projection);
	}

	cv::FileStorage fs(argv[1], cv::FileStorage::WRITE);
	fs << "Resolution_projector" << resolution_projector;
	fs << "Camera_projector_transformation" << camera_projector_transformation;
	fs.release();

	return EXIT_SUCCESS;
}
