#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/persistence.hpp>
 
#include <iostream>
#include <string>
#include <queue>

const unsigned char U8_FULL  = 255;
const unsigned char U8_HALF  = 127;
const unsigned char U8_NONE  =   0;

const signed int NOKEY_ANYKEY = -1;
const int FULL_PERCENTAGE = 100;

const cv::Point2f ORIGIN2D = cv::Point2f(0, 0);

const unsigned char REQUIRED_CORNERS = 4;
cv::Point2f* coordinate_corners_camera = new cv::Point2f[REQUIRED_CORNERS];
cv::Scalar* scalar_corners = new cv::Scalar[REQUIRED_CORNERS];
unsigned int current_corner = 0;
cv::Point2f* coordinate_corners_projector = new cv::Point2f[REQUIRED_CORNERS];

bool mouse_entered = false;
cv::Point2f coordinate_mouse;

const int CROSS_SIZE = 10;
const int CROSS_HSIZE = CROSS_SIZE / 2;
const int CROSS_THICKNESS = 2;

cv::Mat camera_projector_transformation;

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
	for (unsigned int i = 0; i < REQUIRED_CORNERS; ++i) {
		drawCrossOnImage(image, coordinate_corners_camera[i], scalar_corners[i]);
	}
	if (mouse_entered) {
		drawCrossOnImage(image, coordinate_mouse, scalar_corners[current_corner]);
	}
}

void cameraWindowMouseEvent(int event, int x, int y, int flags, void* userdata) {
	coordinate_mouse = cv::Point2f(x, y);
	mouse_entered = true;

	if (flags & cv::EVENT_FLAG_LBUTTON && REQUIRED_CORNERS) {
		coordinate_corners_camera[current_corner] = coordinate_mouse;
		current_corner = (current_corner + 1) % REQUIRED_CORNERS;
		camera_projector_transformation = cv::getPerspectiveTransform(
			coordinate_corners_camera,
			coordinate_corners_projector
		);
	}
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
		std::cout << "Usage: <path to configuration file> <int video device> <path to calibration projection video file>" << std::endl;
		return EXIT_SUCCESS;
	}

	cv::FileStorage read_config;
	read_config.open(argv[1], cv::FileStorage::READ);
	int frames_projector_camera_delay;
	if (read_config["Frames_projector_camera_delay"].isNone()) {
		frames_projector_camera_delay = 5;
	} else {
		read_config["Frames_projector_camera_delay"] >> frames_projector_camera_delay;
	}
	int percentage_projector_background_light;
	if (read_config["Percentage_projector_background_light"].isNone()) {
		percentage_projector_background_light = 39;
	} else {
		read_config["Percentage_projector_background_light"] >> percentage_projector_background_light;
	}
	
	scalar_corners[0] = cv::Scalar(U8_NONE, U8_HALF, U8_FULL);
	scalar_corners[1] = cv::Scalar(U8_NONE, U8_FULL, U8_HALF);
	scalar_corners[2] = cv::Scalar(U8_HALF, U8_NONE, U8_NONE);
	scalar_corners[3] = cv::Scalar(U8_HALF, U8_FULL, U8_NONE);
 
	cv::Mat frame_projector;
	cv::VideoCapture projector_videoreader(argv[3]);
	cv::namedWindow("Projector", cv::WINDOW_NORMAL);
	cv::moveWindow("Projector", 0, 0);
	
	cv::Mat frame_delay_projector;
	cv::namedWindow("Projector delay", cv::WINDOW_NORMAL);
	cv::moveWindow("Projector delay", 300, 0);
	
	cv::Mat frame_camera;
	cv::VideoCapture camera_videoreader(std::stoi(argv[2]));
	cv::namedWindow("Camera", cv::WINDOW_NORMAL);
	cv::moveWindow("Camera", 600, 0);
	cv::setMouseCallback("Camera", cameraWindowMouseEvent, NULL);
	
	cv::Mat frame_projectionelimination;
	cv::namedWindow("Projection elimination", cv::WINDOW_NORMAL);
	cv::moveWindow("Projection elimination", 900, 0);
	cv::createTrackbar("Ratio projector - background light", "Projection elimination", &percentage_projector_background_light, FULL_PERCENTAGE, NULL);
	cv::createTrackbar("Frames projector - camera delay", "Projection elimination", &frames_projector_camera_delay, FULL_PERCENTAGE, NULL);

	cv::Mat frame_projection;
	cv::namedWindow("Projection", cv::WINDOW_NORMAL);
	cv::moveWindow("Projection", 1200, 0);
	
	const cv::Size resolution_projector(projector_videoreader.get(cv::CAP_PROP_FRAME_WIDTH), projector_videoreader.get(cv::CAP_PROP_FRAME_HEIGHT));
	coordinate_corners_projector[0] = cv::Point2f(                    ORIGIN2D.x,                      ORIGIN2D.y);
	coordinate_corners_projector[1] = cv::Point2f(resolution_projector.width - 1,                      ORIGIN2D.y);
	coordinate_corners_projector[2] = cv::Point2f(										ORIGIN2D.x, resolution_projector.height - 1);
	coordinate_corners_projector[3] = cv::Point2f(resolution_projector.width - 1, resolution_projector.height - 1);
	cv::Size resolution_camera(camera_videoreader.get(cv::CAP_PROP_FRAME_WIDTH), camera_videoreader.get(cv::CAP_PROP_FRAME_HEIGHT));
	if (read_config["Camera_projector_transformation"].isNone()) {
		coordinate_corners_camera[0] = cv::Point2f(                 ORIGIN2D.x,                   ORIGIN2D.y);
		coordinate_corners_camera[1] = cv::Point2f(resolution_camera.width - 1,                   ORIGIN2D.y);
		coordinate_corners_camera[2] = cv::Point2f(									ORIGIN2D.x, resolution_camera.height - 1);
		coordinate_corners_camera[3] = cv::Point2f(resolution_camera.width - 1, resolution_camera.height - 1);
		
		camera_projector_transformation = cv::getPerspectiveTransform(
			coordinate_corners_camera,
			coordinate_corners_projector
		);
	} else {
		read_config["Camera_projector_transformation"] >> camera_projector_transformation;
		std::vector<cv::Point2f> points_projector = std::vector<cv::Point2f>(4);
		points_projector.push_back(cv::Point2f(                    ORIGIN2D.x,                      ORIGIN2D.y));
		points_projector.push_back(cv::Point2f(resolution_projector.width - 1,                      ORIGIN2D.y));
		points_projector.push_back(cv::Point2f(									   ORIGIN2D.x, resolution_projector.height - 1));
		points_projector.push_back(cv::Point2f(resolution_projector.width - 1, resolution_projector.height - 1));
		std::vector<cv::Point2f> points_projection = std::vector<cv::Point2f>(4);
		cv::perspectiveTransform(
			points_projector,
			points_projection,
			camera_projector_transformation.inv()
		);
		
		coordinate_corners_camera[0] = points_projection[0];
		coordinate_corners_camera[1] = points_projection[1];
		coordinate_corners_camera[2] = points_projection[2];
		coordinate_corners_camera[3] = points_projection[3];
	}
	read_config.release();
	
	std::queue<cv::Mat> frames_delay_projector;
	while (cv::waitKey(1) == NOKEY_ANYKEY && projector_videoreader.read(frame_projector) && camera_videoreader.read(frame_camera)) {
		drawCornersOnImage(frame_camera);

		cv::imshow("Projector", frame_projector);
		cv::imshow("Camera", frame_camera);
		
		frames_delay_projector.push(frame_projector.clone());
		while (frames_delay_projector.size() > ((unsigned int) frames_projector_camera_delay)) {
			frames_delay_projector.pop();
		}
		if (frames_delay_projector.size() == ((unsigned int) frames_projector_camera_delay)) {
			frame_delay_projector = frames_delay_projector.front();
			cv::imshow("Projector delay", frame_delay_projector);
			cv::warpPerspective(
				frame_delay_projector,
				frame_projectionelimination,
				camera_projector_transformation,
				frame_camera.size(),
				cv::INTER_LINEAR | cv::WARP_INVERSE_MAP,
				cv::BORDER_CONSTANT,
				cv::Scalar(U8_NONE, U8_NONE, U8_NONE)
			);
			
			frame_projectionelimination = frame_camera - (frame_projectionelimination * ((double) percentage_projector_background_light) / (double) FULL_PERCENTAGE);
			
			cv::warpPerspective(
				frame_projectionelimination,
				frame_projection,
				camera_projector_transformation,
				resolution_projector,
				cv::INTER_LINEAR,
				cv::BORDER_CONSTANT,
				cv::Scalar(U8_NONE, U8_NONE, U8_NONE)
			);
			cv::imshow("Projection elimination", frame_projectionelimination);
			cv::imshow("Projection", frame_projection);
		}
	}

	projector_videoreader.release();
	camera_videoreader.release();

	cv::FileStorage write_config(argv[1], cv::FileStorage::WRITE);
	write_config << "Camera_device" << std::stoi(argv[2]);
	write_config << "Resolution_camera" << resolution_camera;
	write_config << "Resolution_projector" << resolution_projector;
	write_config << "Camera_projector_transformation" << camera_projector_transformation;
	write_config << "Frames_projector_camera_delay" << frames_projector_camera_delay;
	write_config << "Percentage_projector_background_light" << percentage_projector_background_light;
	write_config.release();
	
	return EXIT_SUCCESS;
}
