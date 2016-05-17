#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/persistence.hpp>
 
#include <iostream>
#include <string>
#include <queue>

const unsigned char U8_WHITE = 255;
const unsigned char U8_BLACK = 0;
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


int main(int argc, char* argv[]) {
	if (argc != 5) {
		std::cout << "Usage: <path to configuration file> <int video device> <projector resolution width> <projector resolution height>" << std::endl;
		return EXIT_SUCCESS;
	}

	unsigned int frames_projector_camera_delay = 6;
	double RATIO_PROJECTOR_BACKGROUND_LIGHT = 0.3;
	
	cv::FileStorage fs;
	fs.open(argv[1], cv::FileStorage::READ);
	cv::Size resolution_projector;
	fs["Resolution_projector"] >> resolution_projector;
	cv::Mat camera_projector_transformation; 
	fs["Camera_projector_transformation"] >> camera_projector_transformation;
	fs.release();
	
	cv::Mat frame_projector;
	cv::VideoCapture projector_videoreader("./test/Test 1/projector.mp4");
	cv::namedWindow("Projector", cv::WINDOW_NORMAL);
	cv::moveWindow("Projector", 0, 0);
	cv::Mat frame_delay_projector;
	cv::namedWindow("Projector delay", cv::WINDOW_NORMAL);
	cv::moveWindow("Projector delay", 300, 0);
	cv::Mat frame_camera;
	cv::VideoCapture camera_videoreader("./test/Test 1/camera.mp4");
	cv::namedWindow("Camera", cv::WINDOW_NORMAL);
	cv::moveWindow("Camera", 600, 0);
	cv::Mat frame_projectionelimination;
	cv::namedWindow("Projection elimination", cv::WINDOW_NORMAL);
	cv::moveWindow("Projection elimination", 900, 0);
	cv::Mat frame_projection;
	cv::namedWindow("Projection", cv::WINDOW_NORMAL);
	cv::moveWindow("Projection", 1200, 0);
	
	std::queue<cv::Mat> frames_delay_projector;
	while (cv::waitKey(1) == NOKEY_ANYKEY && projector_videoreader.read(frame_projector) && camera_videoreader.read(frame_camera)) {
		cv::imshow("Projector", frame_projector);
		cv::imshow("Camera", frame_camera);
		
		frames_delay_projector.push(frame_projector.clone());
		if (frames_delay_projector.size() > frames_projector_camera_delay) {
			frame_delay_projector = frames_delay_projector.front();
			frames_delay_projector.pop();
			cv::imshow("Projector delay", frame_delay_projector);
			cv::warpPerspective(
				frame_delay_projector,
				frame_projectionelimination,
				camera_projector_transformation,
				frame_camera.size(),
				cv::INTER_LINEAR | cv::WARP_INVERSE_MAP,
				cv::BORDER_CONSTANT,
				cv::Scalar(U8_BLACK, U8_BLACK, U8_BLACK)
			);
			
			frame_projectionelimination = frame_camera - (frame_projectionelimination * RATIO_PROJECTOR_BACKGROUND_LIGHT);
			
			cv::warpPerspective(
				frame_projectionelimination,
				frame_projection,
				camera_projector_transformation,
				resolution_projector,
				cv::INTER_LINEAR,
				cv::BORDER_CONSTANT,
				cv::Scalar(U8_BLACK, U8_BLACK, U8_BLACK)
			);
			cv::imshow("Projection elimination", frame_projectionelimination);
			cv::imshow("Projection", frame_projection);
		}
	}

	projector_videoreader.release();
	camera_videoreader.release();
	
	return EXIT_SUCCESS;
}
