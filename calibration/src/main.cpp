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
	
	cv::Mat frame_projector;
	cv::namedWindow("Projector", cv::WINDOW_NORMAL);
	cv::moveWindow("Projector", 0, 0);

	cv::Mat frame_camera;
	cv::VideoCapture camera_video_reader(std::stoi(argv[2]));
	cv::VideoCapture projector_video_reader("./calibration/test/camera_projector_transformation/big_buck_bunny_1080p_h264.mov");
	cv::namedWindow("Camera", cv::WINDOW_NORMAL);
	cv::moveWindow("Camera", 500, 0);
	cv::setMouseCallback("Camera", cameraWindowMouseEvent, NULL);
	
	while (amount_corners < REQUIRED_CORNERS) {
		if (!camera_video_reader.read(frame_camera)) {
			std::cerr << "Unable to read next frame." << std::endl;
			std::cerr << "Exiting..." << std::endl;
			return EXIT_FAILURE;
		}
		if (!projector_video_reader.read(frame_projector)) {
			std::cerr << "Unable to read next frame." << std::endl;
			std::cerr << "Exiting..." << std::endl;
			return EXIT_FAILURE;
		}
		drawCornersOnImage(frame_camera);
		cv::imshow("Camera", frame_camera);
		cv::imshow("Projector", frame_projector);
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
	
	cv::VideoWriter camera_video_writer(
		"./test/camera.mp4",
		cv::VideoWriter::fourcc('M', 'P', 'E', 'G'),
		25,
		cv::Size(camera_video_reader.get(cv::CAP_PROP_FRAME_WIDTH), camera_video_reader.get(cv::CAP_PROP_FRAME_HEIGHT)),
		true
	);
	cv::VideoWriter projection_video_writer(
		"./test/projection.mp4",
		cv::VideoWriter::fourcc('M', 'P', 'E', 'G'),
		25,
		resolution_projector,
		true
	);
	cv::VideoWriter projector_video_writer(
		"./test/projector.mp4",
		cv::VideoWriter::fourcc('M', 'P', 'E', 'G'),
		25,
		cv::Size(projector_video_reader.get(cv::CAP_PROP_FRAME_WIDTH), projector_video_reader.get(cv::CAP_PROP_FRAME_HEIGHT)),
		true
	);

	cv::namedWindow("Projection", cv::WINDOW_NORMAL);
	cv::moveWindow("Projection", 1000, 0);
	cv::Mat frame_projection;
	while (cv::waitKey(1) == NOKEY_ANYKEY) {
		if (!camera_video_reader.read(frame_camera)) {
			std::cerr << "Unable to read next frame." << std::endl;
			std::cerr << "Exiting..." << std::endl;
			return EXIT_FAILURE;
		}
		if (!projector_video_reader.read(frame_projector)) {
			std::cerr << "Unable to read next frame." << std::endl;
			std::cerr << "Exiting..." << std::endl;
			return EXIT_FAILURE;
		}
		drawCornersOnImage(frame_camera);
		cv::imshow("Camera", frame_camera);
		cv::imshow("Projector", frame_projector);
		cv::warpPerspective(
			frame_camera,
			frame_projection,
			camera_projector_transformation,
			resolution_projector
		);
		cv::imshow("Projection", frame_projection);
		projector_video_writer << frame_projector;
		projection_video_writer << frame_projection;
		camera_video_writer << frame_camera;
	}
	camera_video_reader.release();
	projector_video_reader.release();
	camera_video_writer.release();
	projection_video_writer.release();

	cv::FileStorage fs(argv[1], cv::FileStorage::WRITE);
	fs << "Resolution_projector" << resolution_projector;
	fs << "Camera_projector_transformation" << camera_projector_transformation;
	fs.release();

	return EXIT_SUCCESS;
}
