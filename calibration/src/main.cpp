#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/persistence.hpp>
 
#include <iostream>
#include <string>
#include <queue>

#include "../../scene/src/Calibration.hpp"

unsigned DEFAULT_FRAMES_PROJECTOR_CAMERA_DELAY = 5;
double DEFAULT_PROJECTOR_BACKGROUND_LIGHT = 39;
float DEFAULT_METER = 100.f;

const int CROSS_SIZE = 10;
const int CROSS_THICKNESS = 1;

const cv::Scalar COLOR_A_METER(255, 255,  0);
const cv::Scalar COLOR_B_METER(  0, 255, 255);


unsigned int CONFIGPATH_ARGN = 1;
unsigned int CAMERADEVICE_ARGN = 2;
unsigned int CALIBRATIONPATH_ARGN = 3;

const unsigned char U8_FULL  = 255;
const unsigned char U8_HALF  = 127;
const unsigned char U8_NONE  =   0;

const signed int NOKEY_ANYKEY = -1;
const int INT_FULL_PERCENTAGE = 100;
const double DOUBLE_FULL_PERCENTAGE = 100.0;

const cv::Point2f ORIGIN2D = cv::Point2f(0, 0);

const unsigned char REQUIRED_CORNERS = 4;
unsigned int current_corner = 0;
cv::Point2f* coordinate_corners_camera = new cv::Point2f[REQUIRED_CORNERS];
cv::Point2f* coordinate_corners_projector = new cv::Point2f[REQUIRED_CORNERS];
cv::Scalar* color_corners = new cv::Scalar[REQUIRED_CORNERS];
bool entered_mouse_projection = false;
cv::Point2f coordinate_mouse_projection;

enum METER { METER_A, METER_B };
METER current_meter;
cv::Point2f a_meter;
cv::Point2f b_meter;
bool entered_mouse_meter = false;
cv::Point2f coordinate_mouse_meter;

const int CROSS_HSIZE = CROSS_SIZE / 2;

Calibration* calibration = NULL;
cv::Mat camera_projector_transformation;

void drawCrossOnImage(cv::Mat& image, const cv::Point2f& point, const cv::Scalar& color) {
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

void drawProjectionBoundariesOnImage(cv::Mat& image) {
	cv::Point polypoints[REQUIRED_CORNERS];
	polypoints[0] = coordinate_corners_camera[0];
	polypoints[1] = coordinate_corners_camera[1];
	polypoints[2] = coordinate_corners_camera[3];
	polypoints[3] = coordinate_corners_camera[2];
	const cv::Point* ppt[1] = { polypoints };
	int npt[] = {REQUIRED_CORNERS};
	cv::polylines(
		image,
		ppt,
		npt,
		1,
		true,
		cv::Scalar(255, 255, 255),
		CROSS_THICKNESS,
		cv::LINE_AA
	);
	for (unsigned int i = 0; i < REQUIRED_CORNERS; ++i) {
		drawCrossOnImage(image, coordinate_corners_camera[i], color_corners[i]);
	}
	if (entered_mouse_projection) {
		drawCrossOnImage(image, coordinate_mouse_projection, color_corners[current_corner]);
	}
}

void drawMeterOnImage(cv::Mat& image) {
	cv::line(image, a_meter, b_meter, cv::Scalar(255, 255, 255));
	drawCrossOnImage(image, a_meter, COLOR_A_METER);
	drawCrossOnImage(image, b_meter, COLOR_B_METER);
	if (entered_mouse_meter) {
		switch (current_meter) {
			case METER_A:
				drawCrossOnImage(image, coordinate_mouse_meter, COLOR_A_METER);
				break;
			case METER_B:
				drawCrossOnImage(image, coordinate_mouse_meter, COLOR_B_METER);
				break;
		}
	}
}

void onMouseCalibrateProjection(int event, int x, int y, int flags, void* userdata) {
	coordinate_mouse_projection = cv::Point2f(x, y);
	entered_mouse_projection = true;

	if (event == cv::EVENT_LBUTTONUP) {
		coordinate_corners_camera[current_corner] = coordinate_mouse_projection;
		current_corner = (current_corner + 1) % REQUIRED_CORNERS;
		camera_projector_transformation = cv::getPerspectiveTransform(
			coordinate_corners_camera,
			coordinate_corners_projector
		);
		calibration->setCameraProjectorTransformation(camera_projector_transformation);
	}
}

void onMouseCalibrateMeter(int event, int x, int y, int flags, void* userdata) {
	coordinate_mouse_meter = cv::Point2f(x, y);
	entered_mouse_meter = true;

	if (event == cv::EVENT_LBUTTONUP) {
		switch (current_meter) {
			case METER_A:
				a_meter = coordinate_mouse_meter;
				current_meter = METER_B;
				break;
			case METER_B:
				b_meter = coordinate_mouse_meter;
				current_meter = METER_A;
				break;
		}
	}
}

void onProjectorBackgroundLight(int tracked_int, void *user_data) {
	calibration->setProjectorBackgroundLight((double) tracked_int / DOUBLE_FULL_PERCENTAGE);
}

void onFramesProjectorCameraDelay(int tracked_int, void *user_data) {
	if (tracked_int < 0) {
		calibration->setFramesProjectorCameraDelay(0);
	} else {
		calibration->setFramesProjectorCameraDelay((unsigned int) tracked_int);
	}
}


int main(int argc, char* argv[]) {
	color_corners[0] = cv::Scalar(U8_NONE, U8_HALF, U8_FULL);
	color_corners[1] = cv::Scalar(U8_NONE, U8_FULL, U8_HALF);
	color_corners[2] = cv::Scalar(U8_HALF, U8_NONE, U8_NONE);
	color_corners[3] = cv::Scalar(U8_HALF, U8_FULL, U8_NONE);
	

	if (argc != 4) {
		std::cout << "Usage: <path to configuration file> <int camera device> <path to calibration projection video file>" << std::endl;
		return EXIT_SUCCESS;
	}

	cv::FileStorage read_config;
	char* configpath = argv[CONFIGPATH_ARGN];
	read_config.open(configpath, cv::FileStorage::READ);

	unsigned int frames_projector_camera_delay;
	if (read_config["Frames_projector_camera_delay"].isNone()) {
		frames_projector_camera_delay = DEFAULT_FRAMES_PROJECTOR_CAMERA_DELAY;
	} else {
		signed int int_frames_projector_camera_delay;
		read_config["Frames_projector_camera_delay"] >> int_frames_projector_camera_delay;
		if (int_frames_projector_camera_delay < 0) {
			frames_projector_camera_delay = 0;
		} else {
			frames_projector_camera_delay = (unsigned int) int_frames_projector_camera_delay;
		}
	}
	double projector_background_light;
	if (read_config["Projector_background_light"].isNone()) {
		projector_background_light = DEFAULT_PROJECTOR_BACKGROUND_LIGHT;
	} else {
		read_config["Projector_background_light"] >> projector_background_light;
	}
	if (read_config["Meter"].isNone()) {
		a_meter = cv::Point2f(10, 10);
		b_meter = cv::Point2f(10 + DEFAULT_METER, 10);
	} else {
		float meter;
		read_config["Meter"] >> meter;
		a_meter = cv::Point2f(10, 10);
		b_meter = cv::Point2f(10 + meter, 10);
	}
 
	cv::Mat frame_projector;
	cv::VideoCapture projector_videoreader(argv[CALIBRATIONPATH_ARGN]);
	
	cv::Mat frame_camera;
	int cameradevice = std::stoi(argv[CAMERADEVICE_ARGN]);
	cv::VideoCapture camera_videoreader(cameradevice);
	camera_videoreader.set(CV_CAP_PROP_AUTOFOCUS, 0);
	
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
		std::vector<cv::Point2f> points_projector = std::vector<cv::Point2f>(REQUIRED_CORNERS);
		points_projector.at(0) = cv::Point2f(                    ORIGIN2D.x,                      ORIGIN2D.y);
		points_projector.at(1) = cv::Point2f(resolution_projector.width - 1,                      ORIGIN2D.y);
		points_projector.at(2) = cv::Point2f(									   ORIGIN2D.x, resolution_projector.height - 1);
		points_projector.at(3) = cv::Point2f(resolution_projector.width - 1, resolution_projector.height - 1);
		std::vector<cv::Point2f> points_projection = std::vector<cv::Point2f>(REQUIRED_CORNERS);
		cv::perspectiveTransform(
			points_projector,
			points_projection,
			camera_projector_transformation.inv()
		);
		
		coordinate_corners_camera[0] = points_projection.at(0);
		coordinate_corners_camera[1] = points_projection.at(1);
		coordinate_corners_camera[2] = points_projection.at(2);
		coordinate_corners_camera[3] = points_projection.at(3);
	}
	read_config.release();
	

	calibration = new Calibration(resolution_projector, camera_projector_transformation, frames_projector_camera_delay, projector_background_light);
	
	cv::namedWindow("Projector", cv::WINDOW_NORMAL);
	cv::moveWindow("Projector", 0, 0);
	
	cv::Mat frame_calibrateprojection;
	cv::namedWindow("Calibrate projection", cv::WINDOW_NORMAL);
	cv::moveWindow("Calibrate projection", 300, 0);
	cv::setMouseCallback("Calibrate projection", onMouseCalibrateProjection, NULL);
	
	cv::Mat frame_calibratemeter;
	cv::namedWindow("Calibrate meter", cv::WINDOW_NORMAL);
	cv::moveWindow("Calibrate meter", 600, 0);
	cv::setMouseCallback("Calibrate meter", onMouseCalibrateMeter, NULL);
	
	cv::Mat frame_projectionelimination;
	cv::namedWindow("Projection elimination", cv::WINDOW_NORMAL);
	cv::moveWindow("Projection elimination", 900, 0);
	int track_projector_background_light = round(projector_background_light * DOUBLE_FULL_PERCENTAGE);
	cv::createTrackbar("Ratio projector - background light", "Projection elimination", &track_projector_background_light, INT_FULL_PERCENTAGE, onProjectorBackgroundLight);
	int track_frames_projector_camera_delay = (signed int) frames_projector_camera_delay;
	cv::createTrackbar("Frames projector - camera delay", "Projection elimination", &track_frames_projector_camera_delay, INT_FULL_PERCENTAGE, onFramesProjectorCameraDelay);

	cv::Mat frame_projection;
	cv::namedWindow("Projection", cv::WINDOW_NORMAL);
	cv::moveWindow("Projection", 1200, 0);
	
	while (cv::waitKey(1) == NOKEY_ANYKEY && projector_videoreader.read(frame_projector) && camera_videoreader.read(frame_camera)) {
		cv::imshow("Projector", frame_projector);

		calibration->feedFrameProjector(frame_projector);
		calibration->eliminateProjectionFeedbackFromFrameCamera(frame_projectionelimination, frame_camera);
		calibration->createFrameProjectionFromFrameCamera(frame_projection, frame_projectionelimination);
		cv::imshow("Projection elimination", frame_projectionelimination);
		cv::imshow("Projection", frame_projection);
		
		frame_calibrateprojection = frame_camera.clone();
		frame_calibratemeter = frame_camera.clone();
		drawProjectionBoundariesOnImage(frame_calibrateprojection);
		cv::imshow("Calibrate projection", frame_calibrateprojection);

		drawMeterOnImage(frame_calibratemeter);
		cv::imshow("Calibrate meter", frame_calibratemeter);
	}

	projector_videoreader.release();
	camera_videoreader.release();

	cv::FileStorage write_config(configpath, cv::FileStorage::WRITE);
	write_config << "Camera_device" << cameradevice;
	write_config << "Resolution_camera" << resolution_camera;
	write_config << "Resolution_projector" << resolution_projector;
	write_config << "Camera_projector_transformation" << camera_projector_transformation;
	write_config << "Frames_projector_camera_delay" << (int) frames_projector_camera_delay;
	write_config << "Projector_background_light" << projector_background_light;
	const cv::Point2f diff_meter = b_meter - a_meter;
	write_config << "Meter" << sqrt(abs(diff_meter.x * diff_meter.x + diff_meter.y * diff_meter.y));
	write_config.release();
	
	return EXIT_SUCCESS;
}
